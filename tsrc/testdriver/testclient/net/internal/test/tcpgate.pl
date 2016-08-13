#
# =============================================================================
#  Name          : tcpgate.pl
#  Part of       : TestClient
#  Version       :
#
#  Copyright © 2005 Nokia. All rights reserved.
#  This material, including documentation and any related 
#  computer programs, is protected by copyright controlled by 
#  Nokia Corporation. All rights are reserved. Copying, 
#  including reproducing, storing, adapting or translating, any 
#  or all of this material requires the prior written consent of 
#  Nokia Corporation. This material also contains confidential 
#  information which may not be disclosed to others without the 
#  prior written consent of Nokia Corporation. 
# =============================================================================
#

use IO::Socket;
use IO::Handle;

my $listen_addr = '127.0.0.1';
my $listen_port = 5070;
my $gated_addr = '127.0.0.1';
my $gated_port = 5080;

my $response_max_size = 40960;
my $request_max_size = 5120;

my $ttcn_ctrl = "CTRL/2.0";
my $ttcn_endpdu = "\$";
my $ttcn_req_end = "_END_";

my $ttcn_end_received;


# read command line args
if ( defined( @ARGV[ 0 ] ) )
{
	$listen_addr = @ARGV[ 0 ];
	print "listening addr is: $listen_addr\n";
}
if ( defined( @ARGV[ 1 ] ) )
{
	$listen_port = @ARGV[ 1 ];
	print "listening port is: $listen_port\n";
}
if ( defined( @ARGV[ 2 ] ) )
{
	$gated_addr = @ARGV[ 2 ];
	print "gated addr is: $gated_addr\n";
}
if ( defined( @ARGV[ 3 ] ) )
{
	$gated_port = @ARGV[ 3 ];
	print "gated port is: $gated_port\n";
}

# =====================================================================

$socket = new IO::Socket::INET (
                                  LocalHost => $listen_addr,
                                  LocalPort => $listen_port,
                                  Proto => 'tcp',
                                  Listen => 5,
                                  Reuse => 1
                               );
                                
die "Coudn't open socket" unless $socket;

print "\nTCPToSerial:: Waiting for client on port $listen_port\n";

while ( 1 )
{
	$client_socket = "";

	$client_socket = $socket->accept();
	
	$peer_address = $client_socket->peerhost();
	$peer_port = $client_socket->peerport();
	
	print "\nclient connected\n";
	
	print "open gated port\n";
	$gated_socket = new IO::Socket::INET (
                                  PeerAddr => $gated_addr,
                                  PeerPort => $gated_port,
                                  Proto => 'tcp',
                                  Reuse => 1
                               );
  die "Coudn't open socket" unless $gated_socket;
  
  print "gated connection opened\n";
	
	$connected = 1;
	$ttcn_end_received = 0;
	while ( $connected )
	{
		$num_received;
		$received_data_tcp = receiveData($client_socket, $request_max_size, $num_received);
		if ( $num_received <= 0 )
		{
			print "oops!\n";
			$connected = 0;
		}
		
		if ( $connected )
			{
				print "received from client socket: $received_data_tcp\n";
				
				$gated_socket->write("$received_data_tcp") || break;
				print "wrote to gated socket\n";
				
				$received_data_tcp = "";
				
				$received_data_tcp = receiveData($gated_socket, $response_max_size, $num_received);
				if ( $num_received <= 0 )
				{
					print "oops!\n";
					$connected = 0;
				}
				
				if ( $connected )
				{
					print "received from gated socket: $received_data_tcp\n";
		
					$client_socket->write("$received_data_tcp") || break;
					print "wrote to client socket\n";
				}
			}
	}
	print "disconnected!\n";
}

close $socket;

# =====================================================================

sub receiveData()
{
	$result_data = "";
		
	$done = false;
	while ( 1 )
	{
		$ret = $_[0]->recv($data, $_[1], 0);
		
		unless ( defined($ret) && length($data) )
		{
			resetAll($client_socket, $gated_socket);
			$_[2] = 0;
			return "";
		}
		
		$result_data .= $data;
		
		if ( $result_data =~ m/($ttcn_ctrl(.|\n)*\$)/ )
		{
			print "received valid data\n";
			$result_data = $1;
			
			if ( $result_data =~ m/($ttcn_req_end)/ )
			{
				print "ttcn end req received\n";
				$ttcn_end_received = 1;
			}
			
			$_[2] = length($result_data);
			return $result_data;
		}
	}
	$_[2] = 0;
	return "";
}

sub resetAll()
{
	# send ttcn end req to serial
	unless ( $ttcn_end_received )
	{
		$end_request = sprintf("CTRL/2.0%cREQ%c_END_%c\$\r\n",254,254,254);
		print "trying to send end request: $end_request\n";
		$_[1]->write($end_request);
		print "end request sent!\n";
	}
	
	close $_[0]; 
	close $_[1];
}
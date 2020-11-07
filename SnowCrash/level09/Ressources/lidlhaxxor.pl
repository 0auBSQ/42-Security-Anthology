print "=== LIDL Haxxor ===\n";
print "Your string LIDLed :\n";
for my $i (0..length($ARGV[0]) - 1) {
	print chr(ord(substr($ARGV[0], $i, 1)) - $i);
	$acc++;
}
print "\n";
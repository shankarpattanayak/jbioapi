#-----------------------------------------------------------------------
# File: EXTRACTMDSATTR.PL
#
# Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

$file = shift;
open( FILE, $file ) || die "Can't open $file:$!";
open( RES, ">res.txt" ) || die "Can't open res.txt:$!";
while ( <FILE> )
{
	if ( /(s_MdsAttrInfo_\w+)/ )
	{
		print RES "\t\&$1,\n";
	}
}

close( RES );
close( FILE );

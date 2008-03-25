#!/usr/bin/env perl

$language = "Hebrew";
$prefix = "iw";
$script = "hebrew";

$alphabet = [
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�']],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�','�'] ],
['�',    ['�'] ],
['�',    ['�','�'] ],
['�',    ['�','�'] ],
['�',    ['�'] ],
['�',    ['�']],
['�',    ['�','�'] ],
['�',    ['�','�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ],
['�',    ['�'] ]
];

$ligatures = [



];

@special = ('?', '!', '.', ';', '�', 'letters',  '-');

# first lower or upper case?

$sortcase = "Aa";
#$sortcase = "aA";

do 'make-rules.pl';

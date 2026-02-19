# CLAUDE.md

## Project Overview
MPint shall become A C++(14) class which can be used instead of existing
native integer types in legacy C/C++ code.
There is an empty shell for that class in MPint.hpp.
For now, MPint should just be a proxy to "signed long int", as signified by
the private member variable "mVal". For the future, this is going to replaced
by an instance of some multi precision integer type from e.g. GMP, PARI, etc.
The point is to provide overloaded operators, so that the delicate
arithmetic expressions in the legacy stuff (from 1990ies math research)
do not have be rewritten in terms of methods like "c=add(a,b)" instead of
"c=a+b", whis is extremely error prone, and even harder to read and maintain than
what currently exists.

## Development Guidelines
Coding standards and conventions: no prefs so far, tbd later
File structure preferences: no prefs so far, tbd later
Testing approaches: no prefs so far, tbd later

## Important Commands
Build commands: come up with a sensible Makefile
Test commands: testing tbd later

## What I've done in the meantime
No changes from my side. I've started a claude code session to
test the 'script -a claude ...' approach, more precisely I used
'script -a mpint-transcript.txt -c "claude --continue" '.
There are multiple issues with that.
1st: 'claude --continue' seems to repdislay the complete conversation
from the start of the session. This collides with 'script -a ..."
obviously.
2nd: 'script' stores all the nonprintable control characters which
renders the transcription to be gibberish. Look at the latest part of 
'mpint-transcript.txt' to get an impression.

On a side note, make target clean fails when 'bin/demo' is not present, e.g.
after a fresh checkout from git.

## What to do for you right now
Come up with some better suggestions for saving transcripts of our sessions incrementally,
and uncluttered.
Please modify the Makefile, so that 'make clean' does not fail when 'bin/demo' is not present.


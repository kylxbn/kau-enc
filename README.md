# kau-enc
Kyle's Experimental Audio Codec (encoder)

This is an experimental project with the aim of creating my own lossy audio codec. This works... kind of... with the caveat that this
is extremely inefficient as a lossy audio codec (considering that Opus can make acceptable audio at 24kbps).

This works by performing a FFT on the signal, records each frequencies and their amplitude several times every second... and that's it.

I mean, I was just a kid when I made this so please don't expect much. But it was a fun project anyway.

I made this on a Pentium 4 HT desktop PC with Windows XP. Yeah.

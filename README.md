# Associative Neural Oscillators
`assoc-neural-oscs` is a collection of programs which simulate and explore the ability of [neural oscillators](http://en.wikipedia.org/wiki/Neural_oscillation) to "remember" phase associations amongst themselves.  Specifically, the programs study [Pyramidal-Interneuron gamma-frequency oscillators](http://www.ncbi.nlm.nih.gov/pubmed/15802007) (PING oscillators), which resemble networks found in the cortex and hippocampus.  For more information on the neuroscience behind the project, see the [literature review](https://github.com/winsto99/assoc-neural-oscs/raw/master/HaszMiller2012_Associative-Neural-Oscillators-Review.pdf) which discusses the theory which inspired the code.


# Usage
The project is written in `C`, so `gcc` and `make` are required to compile the code.

Navigate into each of the main folders (numbered folders) and follow the directions of the README files in each.  Usually you can just navigate into a folder and execute the code by running the command `./run.sh`.

There are also many math and neuroscience-related utilities in the `/utils` folder, which are used by the functions in the main folders, but which may be useful individually.

The routines output data into ascii text files, so you can use your preferred graphing utility.  Alternatively, you can use the provided python plotting tools in `/graphing`.  To use these tools you will need python installed, along witht the python packages [`numpy`](http://www.numpy.org/) and [`matlibplot`](http://matplotlib.org/)


# Copyright
Copyright (C) 2012 Brendan Hasz

[bhasz@brandeis.edu](mailto:bhasz@brandeis.edu)

[www.cs.brandeis.edu/~bhasz/main.php](www.cs.brandeis.edu/~bhasz/main.php)

[Brandeis University](http://www.brandeis.edu/), Waltham, MA, USA


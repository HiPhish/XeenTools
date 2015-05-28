#################################################
XeenTools - Open-Source Library for World of Xeen
#################################################

XeenTools is an open-source library and collection of command-line tools for
working with resource files of the *Might & Magic: World of Xeen* games, namely
*Might & Magic IV: Clouds of Xeen* and *Might & Magic IV: Darkside of Xeen*.

The library is meant for use in larger projects while the command-line tools
allow users to extract files or parts of files for further conversion.

Knowledge of the file formats is required for understanding how things fit
together. You do not have to know *how* exactly the file formats work, that is
what the library is for, but you have to know *where* the data you are looking
for is stored and what data you need in the first place.

Building
########

A C11 standard compliant compiler is required, and there are no library
dependencies. There is a makefile in the *source* directory, but at the moment
it is more like duckt tape and bubble gum rather than a one-step make.

Usage
#####

For now the entire thing is considered highly unstable, meaning one commit
could break compatibility completely. As such it is not recommended for use.

Versioning
##########

XeenTools uses `Semantic Versioning`__

All releases with the same *major* version are guaranteed to be backwards
compatible. Releases that add new features but retain compatibility increment
the *minor* number. Releases that add no features and don't change
compatibility increment the *patch* number.

Major version 0 is not yet production ready and compatibility can bread without
any notice. At the moment we are not even at version 0.x.x yet.

__ SemVer_
.. _SemVer: http://semver.org

Progress
########

So far the following file formats are supported:

- [o] ATT sprite files for attack frames.
- [o] CC files, containers that hold other files.
- [o] CFG configurations for DOS.
- [ ] CHR
- [o] DAT sprite info files for objects.
- [o] Environment sets
- [o] Copy-protection files
- [o] FAC
- [o] FNT font files
- [o] FWL
- [o] GND ground sprits
- [ ] M
- [ ] MOB
- [o] MON sprite files for idle frames.
- [ ] OBJ
- [o] PAL palette files.
- [ ] PTY
- [o] SKY sky sprites
- [o] sprite files in general
- [ ] SRF
- [ ] SWL
- [ ] TIL
- [ ] TXT
- [ ] VGA
- [ ] VOC

Git branching model
###################

There are two main branches, *Devlop* and *Master*, as well as many
topic-branches that get created and deleted as they are needed.

TL;DR: if you want a stable release use the *Master* branch. (currently there
is no master yet)

.. code::

    >====[ T I M E ]===========================================================>

                                    +--+ [Hotfix]
                                   /    \
    --[Master]--------------+--+--/------+------------------------------------->
                           /    \         \
     [release client] +---+      \         \           +-----+ [aborted release]
                     /            \         \         /       \
    --[Develop]-\---/--\------+----+---+-----+----\--/---------+-----+--------->
                 \      \    /        /            \                /
                  \      +--/--------+ [Feature]    \              /
                   \                                 \            /
                    +---------------------------------+----------+ [Feature]

The *Develop* branch is the "dirty" branch to do development on. Smaller
changes can be made on this branch, but larger *feature* topics must be
branched off. Feature branches can be merged back into the development branch
if needed and they can merge in the current development to stay up to date.

Once the feature is ready it can be merged into the development branch for the
last time. The feature branch is then deleted.

Once enough features have accumulated for a release a *release client* branch
is branched off the development branch. This branch is under feature freeze, no
new features may be added. The point of this branch is to prepare for release,
i.e. fix bugs, write documentation and so on. The version number of the release
is decided upon at this point.

If the release has to be abored the branch is merged back into the development
branch and deleted. Otherwise it is merged into the *Master* branch. Every
commit on the master branch is a new release by definition and guaranteed to be
production-ready. Every release is tagged with the version number. The release
is then merged back into the development branch.

If a release is broken and needs a hotfix a *Hotfix* branch if branched off
that particular release.  After it has been fixed it is merged back into the
master branch for a new release and from there merged into development. That
way the master stays clean and the development still gets the fix.

Further documentation
#####################

The *documentation* directory contains forther reading, in particular the style
guidelines and the user manual. At least it will eventually.

License
#######

The MIT License (MIT)

Copyright (c) 2015 "HiPhish"

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
License

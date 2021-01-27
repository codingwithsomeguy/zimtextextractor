# textextractor, for zim html dumps like the wikipedia

Early dev for a C++ tool to parse a zim file (such as the kiwix top 100 wikipedia articles), parse the html (via lexbor), and extract the text content for further analysis.

A small (1.2MB) zim file based on the top 100 English Wikpedia articles: [wikipedia_en_100_mini_2021-01.zim](https://dumps.wikimedia.org/other/kiwix/zim/wikipedia/wikipedia_en_100_mini_2021-01.zim)

Assumes [libzim](https://github.com/openzim/libzim) and [lexbor](https://github.com/lexbor/lexbor) are compiled under this directory (not installed). The build is fragile and should be burned and rebuilt.

Barely tested, use at your own risk.

```bash
# after adding the deps, see libzim/README.md
cd libzim
meson . build
ninja -C build
cd ..

# See lexbor/INSTALL.md
cd lexbor
# TODO: use a build dir instead
cmake . -DLEXBOR_BUILD_TESTS=OFF -DLEXBOR_BUILD_EXAMPLES=OFF -DLEXBOR_BUILD_SEPARATELY=ON
make -j11
cd ..

```


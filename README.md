# Fast String Similarity

3x faster that JS implementation.

## Building

To compile the extension for the first time, run

```
$ npm i
$ npm run configure
$ npm run build
```

All subsequent builds only need `npm run build`

You can confirm everything built correctly by [running the test suite](#to-run-tests).

### Working With the Extension Locally

After building:

```node
$ node
> var fsc = require('fast-string-similarity')
undefined
> fsc.computeStringSimilarity("the quick brown fox", "the quick not brown fox")
0.8484848484848485
```

### To run tests:

```
$ npm test
```

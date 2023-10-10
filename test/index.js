var fsc = require('../');
var assert = require('assert');

function computeStringSimilarityJS(first, second) {
  first = first.replace(/\s+/g, '')
  second = second.replace(/\s+/g, '')

  if (first === second) return 1 // identical or empty
  if (first.length < 2 || second.length < 2) return 0 // if either is a 0-letter or 1-letter string

  let firstBigrams = new Map()
  for (let i = 0; i < first.length - 1; i++) {
    const bigram = first.substring(i, i + 2)
    const count = firstBigrams.has(bigram) ? firstBigrams.get(bigram) + 1 : 1

    firstBigrams.set(bigram, count)
  }

  let intersectionSize = 0
  for (let i = 0; i < second.length - 1; i++) {
    const bigram = second.substring(i, i + 2)
    const count = firstBigrams.has(bigram) ? firstBigrams.get(bigram) : 0

    if (count > 0) {
      firstBigrams.set(bigram, count - 1)
      intersectionSize++
    }
  }

  return (2.0 * intersectionSize) / (first.length + second.length - 2)
}

describe('fast string compare', function() {
  it('should identify equal strings', function() {
    assert.equal(fsc.computeStringSimilarity("abc", "abc"), 1);
  });

  it('should identify similar strings', function() {
    assert.equal(fsc.computeStringSimilarity("the quick brown fox", "the quick not brown fox"), 0.8484848484848485);
  });

  it('should be faster than the JS implementation', function() {
    // Runs the native node module 1000 times and the JS implementation 1000 times
    const stringA = [...Array(10000)].map(() => "the quick brown fox").join(" ")
    const stringB = [...Array(10000)].map(() => "the quick not brown fox").join(" ") 

    const startJs = new Date()
    computeStringSimilarityJS(stringA, stringB)
    const endJs = new Date()

    const startNative = new Date()
    fsc.computeStringSimilarity(stringA, stringB)
    const endNative = new Date()
    assert.equal(endNative - startNative < endJs - startJs, true)
  });
});

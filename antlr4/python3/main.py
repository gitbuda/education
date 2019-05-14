#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# References:
#   * https://github.com/antlr/antlr4/blob/master/doc/getting-started.md
#   * https://github.com/antlr/antlr4/blob/master/doc/python-target.md
#   * https://github.com/jszheng/py3antlr4book

import sys

from antlr4 import FileStream, CommonTokenStream, ParseTreeWalker

from grammar.TestLexer import TestLexer
from grammar.TestParser import TestParser
from grammar.TestListener import TestListener


class TestPrinter(TestListener):
    def exitStartTest(self, ctx):
        print("  Keyword -> %s" % ctx.getChild(0).getText())
        for i in range(1, ctx.getChildCount()):
            print("    ID -> %s" % ctx.getChild(i).getText())


def main(argv):
    input_stream = FileStream(argv[1])
    lexer = TestLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = TestParser(stream)
    tree = parser.startTest()
    print("Abstract Syntax Tree: %s\n" % tree.toStringTree(recog=parser))
    print("Simple visitor:")
    walker = ParseTreeWalker()
    printer = TestPrinter()
    walker.walk(printer, tree)


if __name__ == '__main__':
    main(sys.argv)

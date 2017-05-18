###########################################################################################
# This file is a driver for corpus creator class ##########################################
# Type "python driverCorpus nps.txt context.txt matrix.txt" on your shell #################
###########################################################################################

from gensim import corpora, models, similarities
from corpusBuilder import corpusConstructor
import logging
import time
import sys
import os

############################################################################################
######################### driver for context based textual analysis framework ##############
############################################################################################

#logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

############################################################################################
c = corpusConstructor(True)       			                 # create the object
######### read input - create bag of context - create corpus - query #######################
c.readLine(sys.argv[1], sys.argv[2])

###########################################################################################
# Uncomment this rows if you want perform matrix consruction and LSA
#d = c.makeBagOfWords(sys.argv[3])
#corpus = c.makeCorpusObject(d)
###########################################################################################

c.corpusLsaAndQuery()
############################################################################################
resultSet = c.resultPrint()
############################################################################################
os.execlp("./MakerRdf", "./MakerRdf", resultSet[0][0 : len(resultSet[0])] + ".txt", resultSet[0][0 : len(resultSet[0])] + ".rdf", resultSet[1][0 : len(resultSet[1])]);

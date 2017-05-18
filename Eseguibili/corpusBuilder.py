#######################################################################################################
# This script use gensim library to perform latent semantic analisys on a given dataset ###############
# Please read note file to understand how to use it ###################################################
# Author: Alessandro Merola ###########################################################################
#######################################################################################################
from gensim import corpora, models, similarities

# implements the corpus construction
class corpusConstructor:

	# initialize instance variables
	def __init__(self, verbose = False):
		self.verbose = verbose
		self.words = [] # list of words
		self.contexts = [] # list of contexts
		self.sortedResult = [] # will hold result
		self.query = [] # will hold words query
		self.num_t = 0


	# read all lines from a specified file
	def readLine(self, wordsFile, contextsFile):
		if self.verbose:
			print "Reading lines from " + str(wordsFile)
		with open(wordsFile) as myfile:
			for line in myfile:
				self.words.append(line)
		if self.verbose:
			print "Reading lines from " + str(contextsFile)
		with open(contextsFile) as myfile:
			for line in myfile:
				self.contexts.append(line)


	# performing the tfidf procedure
	def termFrequencyInverseTermFrequency(self, corpusObj):
		if self.verbose:
			print "Performing tfIdf"
		tfidf = models.TfidfModel(corpusObj) # performing term-frequency-inverse-term-frequency
		return tfidf 


	# print the specified list
	def printThis(self, selected):
		if selected == "WORDS":
			for word in self.words:
				print word
		if selected == "CONTEXTS":
			for context in self.contexts:
				print context


	# create the texts object
	# using bag-of word representation for contexts
	def makeBagOfWords(self, matrixFile):
		if self.verbose:
			print "Making text object"
		texts = []
		for context in self.contexts:
			contextVector = []
			with open(matrixFile) as myfile:
				for line in myfile:
					if str(self.contexts[int(line.split("\t")[1])-1]) == str(context):
						if int(line.split("\t")[0]) < 2000:
							for i in range(int(line.split("\t")[2])):
								contextVector.append(self.words[int(line.split("\t")[0])-1][0:len(self.words[int(line.split("\t")[0])-1])-1])
				texts.append(contextVector)
		return texts


	# create a corpus object
	def makeCorpusObject(self, textsObj):
		if self.verbose:
			print "Making corpus object"
		dictionary = corpora.Dictionary(textsObj)
		dictionary.save('../Temporanei/dictionary.dict') # save the dictionary
		corpus = [dictionary.doc2bow(text) for text in textsObj] # create corpus object
		corpora.MmCorpus.serialize('../Temporanei/corpus.mm', corpus) # save the corpus
		return corpus


	# performing lsa and query
	def corpusLsaAndQuery(self):
		dictionary = corpora.Dictionary.load('../Temporanei/dictionary.dict') # read the dictionary from file
		corpus = corpora.MmCorpus('../Temporanei/corpus.mm') # read corpus from file
		lsi = models.LsiModel(corpus, id2word = dictionary, num_topics = 1344) # perform the lsi
		self.num_t = 1344

		with open("../Temporanei/tmp2.txt") as myfile:
			for line in myfile:
				self.query.append(line[0:len(line)-1]) # addind without carriege return

		vec_bow = dictionary.doc2bow(self.query)

		vec_lsi = lsi[vec_bow] # convert the query to LSI space
		index = similarities.MatrixSimilarity(lsi[corpus]) # transform corpus to LSI space and index it
		index.save('../Temporanei/lsaResult.index')
		sims = index[vec_lsi] # perform a similarity query against the corpus
		self.sortedResult = sorted(enumerate(sims), key = lambda item: -item[1])
		return self.sortedResult


	# print result of query
	def resultPrint(self):
		fileOutput = "../Risultati/"
		query = ""
		for i in range(len(self.query)):
			fileOutput = fileOutput + self.query[i] + "_"
			query = query + " " + self.query[i]

		fileOutput[0 : len(fileOutput) - 1] + ".txt"
		with open(fileOutput[0 : len(fileOutput) - 1] + ".txt", "w") as myfile:
			for x in self.sortedResult:
				myfile.write("" + str(self.contexts[x[0]][0:len(self.contexts[x[0]])-1]) + "\t" + str(x[1]) +"\n")

		return [fileOutput[0 : len(fileOutput) - 1], query.strip()]

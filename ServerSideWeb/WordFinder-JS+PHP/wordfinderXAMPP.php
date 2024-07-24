<?php
	error_reporting(0);
	
	//echo "hi"; debug
	
	//note: below url may no longer exist, swap to Dictionary.txt, if needed
	$wordList = file_get_contents('https://gist.githubusercontent.com/wchargin/8927565/raw/d9783627c731268fb2935a731a618aa8e95cf465/words');
	
	if ($_GET['wordIn'] == "") {
		exit(0);
	}
	
	$queryTerm = "/.*" . $_GET['wordIn'] . ".*/";
	//echo "$queryTerm<br>";
	
	$search = preg_match_all($queryTerm, $wordList, $results);
	
	$resultsListSize;
	
	if (count($results[0]) < 10) { 
		$resultsListSize = count($results[0]);
	} else {
		$resultsListSize = 10;
	}
	
	$regexToBold = "/" . $_GET['wordIn'] . "/"; //for char highlighting
	//echo "Regex to bold: $regexToBold<br>";
	for ($result = 0; $result < $resultsListSize; ++$result) {
		//https://stackoverflow.com/questions/31606793/make-certain-characters-of-a-word-from-string-bold#:~:text=%24text%20%3D%20preg_replace(%27%2F%5CS*(%27.,should%20do%20it%20for%20you.
		$results[0][$result] = preg_replace($regexToBold, "<span style='color:blue'><b>" . $_GET['wordIn'] . "</b></span>", $results[0][$result]);
		echo $results[0][$result] . "<br>";
	}
	
	//no need to run levenshtein search if result
	//limit is already reached
	if ($resultsListSize >= 10) { 
		exit(0); 
	} 
											
	//if there aren't 10 results for exact matches to the query, will search for
	//similar matches
	
	//levenshtein
	$wordIn = $_GET['wordIn'];
	$wordInLevenshtein = $wordIn;
	$queryTermSimilar = "/.*(". $wordIn . ").*";
	
	$groupNum = 1; //for bolding similar char match later
	
	//wrong character
	for ($char = 0; $char < strlen($wordIn); ++$char) {
		$wordInLevenshtein[$char] = '.';
		$queryTermSimilar = $queryTermSimilar . "|.*(" . $wordInLevenshtein . ").*";
		$wordInLevenshtein = $wordIn;
		
		$groupNum++;
	}
		
	//skipped a letter
	$levBegin = $wordInLevenshtein;
	$levEnd = $wordInLevenshtein;
	
	//get skipped first letter regex
	$queryTermSimilar = $queryTermSimilar . "|.*(" . substr($wordInLevenshtein, 1) . ").*";
	$wordInLevenshtein = $wordIn;
		
	$groupNum++;
	
	for ($char = 0; $char < strlen($wordIn); ++$char) {
		//https://www.php.net/manual/en/function.strrev.php
		$levBegin = strrev(substr(strrev($wordInLevenshtein), strlen($wordIn) - $char - 1)); //extremely inefficient
		$levEnd = substr($wordInLevenshtein, $char+2);
		$wordInLevenshtein = $levBegin . $levEnd;
		$queryTermSimilar = $queryTermSimilar . "|.*(" . $wordInLevenshtein . ").*";
		$wordInLevenshtein = $wordIn;
		$levBegin = $wordInLevenshtein;
		$levEnd = $wordInLevenshtein;
		
		$groupNum++;
	}
		
	$queryTermSimilar = $queryTermSimilar . "/";
	//echo "levenshtein regex: $queryTermSimilar<br><br>";
		
	$searchSimilar = preg_match_all($queryTermSimilar, $wordList, $resultsSimilar);
		
	//https://www.geeksforgeeks.org/php-append-one-array-to-another/
		
	if (count($resultsSimilar[0]) < (10 - $resultsListSize)) { //don't return more results then
		$resultsListSize = count($results[0]);				   //remaining amount after exact
	} else{													   //matches
		$resultsListSize = 10 - $resultsListSize;
	}
		
	$regexToBold = preg_replace("/\.\*/", "", $queryTermSimilar);
	//echo "levenshtein regex to bold: $regexToBold<br>";
	for ($result = 0; $result < $resultsListSize; ++$result) {
		
		//dupe check with exact match results list
		//echo "does " . $resultsSimilar[0][$result] . " == " . strip_tags($results[0][$result]) . "<br>";
		//https://www.php.net/manual/en/function.strcmp.php
		if (strcmp($resultsSimilar[0][$result], strip_tags($results[0][$result])) == 0) { //https://www.php.net/manual/en/function.strip-tags.php
			//echo "dupe found";
			break; 
		}
		
		//bolding similar match
		for ($group = 1; $group < $groupNum; ++$group) {
			//echo "$groupNum<br>";
			for ($bold = 0; $bold < count($resultsSimilar[$group]); ++$bold) {
				//echo "Results[group][bold]: " . $resultsSimilar[$group][$bold] . "<br>";
				if (($resultsSimilar[$group][$bold] != "") && (str_contains($resultsSimilar[0][$result], $resultsSimilar[$group][$bold]))) {
					//echo "bolding regex";
					//https://stackoverflow.com/questions/31606793/make-certain-characters-of-a-word-from-string-bold#:~:text=%24text%20%3D%20preg_replace(%27%2F%5CS*(%27.,should%20do%20it%20for%20you.
					$resultsSimilar[0][$result] = preg_replace($regexToBold, "<span style='color:green'><b>" . $resultsSimilar[$group][$bold] . "</b></span>", $resultsSimilar[0][$result]);
					break;
				}
			}
		}
		/*
		for ($bold = 0; $bold < count($resultsSimilar[1]); ++$bold) {
			if ($resultsSimilar[0][$bold] == $resultsSimilar[0][$result]) {
				$resultsSimilar[0][$result] = preg_replace($regexToBold, "<span style='color:green'><b>" . $resultsSimilar[1][$result] . "</b></span>", $resultsSimilar[0][$result]);
			}
		}
			
		$resultsSimilar[0][$result] = preg_replace($regexToBold, "<span style='color:green'><b>" . $resultsSimilar[0][$result] . "</b></span>", $resultsSimilar[0][$result]);
		*/
		echo $resultsSimilar[0][$result] . "<br>";
	}
?>
<?php
	
	$funnytable = '<!DOCTYPE html><html><head><title>funny table</title></head><body><table style="border-spacing:0;">';
			
	for ($pageNum = 2; $pageNum <= 35; $pageNum++) {
		$pageNumStr = strval($pageNum);
		$webpage = file_get_contents('https://www.outofcontextquotes.com/wordpress/?paged=' . $pageNumStr);
		$foundQuote = preg_match_all('/entry-content">[^&]+(.+)<\/p>/', $webpage, $matches);
		for ($quote = 0; $quote < count($matches[1]); $quote++) {
			$funnytable = $funnytable . '<tr><td style="border-style:solid;">' . $matches[1][$quote] . '</td></tr>';
		}
	}
	
	$funnytable = $funnytable . '</table></body></html>';
	
	echo $funnytable;
	
?>
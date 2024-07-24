<?php
	$imgID = $_GET['id'];
	$dbHandle = new PDO('mysql:host=localhost;dbname=sagesight', 'sagesight', 'HellIsFull');
	$imgData = "";
	$imgGet = $dbHandle->prepare("SELECT PhotoData from Photos where ID = ?");
	if($imgGet->execute(array($imgID))) {
		$imgData = $imgGet->fetchAll();
	} else {
		exit(0);
	}
	//$thumbnail = "$_FILES['fileUpload'][tmp_name']_thumbnail";
	$thumbnail = "-"; //must be this for thumbnail command?
	//$thumbnail = fopen('thumbnail', 'r+');
	//echo $thumbnail/*->{'$filename'}*/;
	$HEIGHT = 100;
	//create thumbnail
	if($imgFormat == "image/jpeg") {
		$command = "djpeg < " . $_FILES['fileUpload']['tmp_name'] . "| pnmscale -ysize $HEIGHT | cjpeg > " . $thumbnail;
	} else {
		$command = "giftopnm < " . $_FILES['fileUpload']['tmp_name'] . "| pnmscale -ysize $HEIGHT | cjpeg > " . $thumbnail; //concatenate command around $_FILES['fileUpload']['tmp_name']
	}
	print "$command\n";
	system($command);
	echo file_get_contents($thumbnail);
	echo $imgData[0][0];
?>
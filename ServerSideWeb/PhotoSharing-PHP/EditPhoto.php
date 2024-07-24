<?php
	error_reporting(0);
	require("Login/check.php");
	
	$id = $_GET['id'];
	//start of html
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Edit Photo</title>
	</head>
	<body>";
	
	//display photo
	$displayAttrs = array();
	$dbHandle = new PDO ('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	$displayReq = $dbHandle->prepare("SELECT Height, Width, Format FROM SagePhotos WHERE ID = ?");
	if ($displayReq->execute(array($id))) {
		$displayAttrs = $displayReq->fetchAll();
	}
	echo "<img src='GetImage.php?id=" . $id . "' height='" . $displayAttrs[0][0] . "' width='" . $displayAttrs[0][1] . "' type='" . $displayAttrs[0][2] . "'><br>";
	
	//run sql before pulling from database
	//add kw
	$newKWs = preg_split("/, /", $_REQUEST['addKWs']);
	//print_r($newKWs);
	
	foreach($newKWs as $kw) {
		if ($kw != "") {
			$dupeCheck = $dbHandle->prepare("SELECT Keyword FROM SageKeywords WHERE Keyword = ? and PhotoID = ?");
			if ($dupeCheck->execute(array($kw, $id))) {
				if ($dupeCheck->rowCount() == 0) {
					$bannedKWCheck = $dbHandle->prepare("SELECT word FROM SageBannedKWs WHERE Word=?");
					if($bannedKWCheck->execute(array($kw))) {
						if($bannedKWCheck->rowCount() == 0) {
							
							$add = $dbHandle->prepare("INSERT INTO SageKeywords (PhotoID, Keyword) VALUES (?, ?)");
							if($add->execute(array($id, $kw))) {
								echo $kw . " has been added to photo " . $id . "<br>";
							} else {
								echo "THE KW ADD IS BWOKIE NED REPAIRS BEEP BEEP";
								exit(0);
							}
						} else {
							echo "YOU A BULLI ";
							$SageBannedKWs = $bannedKWCheck->fetchAll();
							foreach($SageBannedKWs[0] as $key => $word) {
								if ($key != "word") {
									echo $word . " IS BAD WORD :angy:<br>";
								}
							}
						}
					} else {
						echo "Banned word check no work >.<";
						exit(0);
					}
				} else {
					echo "that word was there already tho";
				}
			} else {
				echo "dupe check was sad ;-;";
			}
		}
	}
	
	//delete keyword
	$delKWs = isset($_REQUEST['delKWs']) ? $_REQUEST['delKWs']: '';
	//print_r($delKWs);
	foreach($delKWs as $kw) {
		$del = $dbHandle->prepare("DELETE FROM SageKeywords WHERE Keyword=? AND PhotoID=?");
		if($del->execute(array($kw, $id))) {
			echo $kw . " deleted from photo " . $id;
		} else {
			echo "DEWETE NO WORK *sniffle*";
			exit(0);
		}
	}
	
	//echo form start
	echo "<form action='EditPhoto.php?id=" . $id . "' method='POST' enctype='multipart/form-data'>";
	
	//delete section
	foreach($dbHandle->query("SELECT Keyword FROM SageKeywords WHERE PhotoID=$id") as $kw) {
		echo "<input type='checkbox' id='delKWs[]' name='delKWs[]' value='" . $kw['Keyword'] . "'>
		<label for='delKWs[]'>" . $kw['Keyword'] . "</label><br>";
	}
	
	//add section
	echo "<label for='addKWs'>Add keyword - please don't put spaces in your Keywords, separate them with a space and comma (blood, fuel, mankind)</label>
		<input type='text' id='addKWs' name='addKWs'><br>";
	
	//rest of html
	echo "		<input type='submit' value='Submit Changes'><br>
		</form>
		<a href='DelPhoto.php?id=" . $id . "'><button type='button'>Delete Photo</button></a><br>
		<a href='Login/Protected.php'><p>Home</p></a>
	</body>
</html>";
?>
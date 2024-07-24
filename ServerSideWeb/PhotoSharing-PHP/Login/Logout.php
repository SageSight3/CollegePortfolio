<?php
	session_start();
	$_SESSION ['logged_in'] = false;
	
	echo "<p>You've logged out</p><br><p><a href='Login.php'>Click here to return to the log in page</a></p>";
?>
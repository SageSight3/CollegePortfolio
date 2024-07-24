<?php
	session_start();
	//print_r($_SESSION);

	if ($_SESSION['logged_in'] == 1)
	{
		//print "Welcome<br>";
		// Cannot exit here.  Will stop the page that requires this from 
		// rendering!
	}
	else {
		header("location:Login.php");
		exit(0);		
	}
?>
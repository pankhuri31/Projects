<?php

require("res/config.php");
if(isset($_SESSION['user']))
{
	die("You are already logged in");
}
?>
<html>
<head>
<title>Irrigation Enterprise</title>
<LINK REL=StyleSheet HREF="style.css" TYPE="text/css" MEDIA=screen>
<style>
.table
{
	margin-top:10px;
	margin-left:400px;
}
#al
{
margin-left:600px;
}
#h
{
color:white;
font-family:"Comic Sans MS", cursive, sans-serif;
}
</style>
</head>
<body>

	<div id="header">
	<h1 id="h">Login</h1>
	</div>
<form action="" method="POST" class="form">
<table class="table">
<tr class="table"><td class="table"><label for="user">User:</label></td><td><input type="text" name="user"/></td></tr>
<br/>
<br/>
<tr class="table"><td class="table">
<label for="passwd">Password:</label></td><td><input type="password" name="passwd"/></td></tr>
<br/><br/>
</table>
<br/>
<input type="submit" name="login" value="Login" id="al"/>
</form>
</body>


<?php
if (isset($_POST['user'],$_POST['passwd']))
{
$_POST['user']=trim($_POST['user']);
$_POST['passwd']=trim($_POST['passwd']);
}
//echo $_POST['user'],$_POST['passwd'];
if(!empty($_POST['user']) && !empty($_POST['passwd']) && isset($_POST['user'],$_POST['passwd'],$_POST['login']))
{
	$chk=mysql_query("SELECT * FROM members WHERE username='$_POST[user]'");
	if(!$chk)
	{ die("select".mysql_error());}
	$chk2=mysql_num_rows($chk);
	$arr=mysql_fetch_array($chk);
	if($arr["passwd"]==$_POST["passwd"])
	{
		echo "helo";
		$_SESSION['valid']=0;
		$_SESSION['user']=trim($_POST['user']);
		$_SESSION['pwd']=trim($_POST['passwd']);
		echo "<h1>YAYY</h1>";
		header("Location:index.php");
	}
	else
	{
		echo "<h1>DON'T tresspass</h1>";
	}
	unset($_POST['user'],$_POST['passwd']);
}
else if(isset($_POST['login']))
{
	echo "<h1>Fill in all d fields</h1>";
}
?>
</html>
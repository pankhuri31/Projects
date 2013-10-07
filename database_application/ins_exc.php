<html>
<?php
session_start();
require("res/config.php");
if(isset($_SESSION['user']))
{
$sql=mysql_query("select insert_permission from members where username='$_SESSION[user]'");
$row=mysql_fetch_array($sql);
if ($row['insert_permission']==0)
header("Location: index.php");
}
if (!isset($_SESSION['user']))
{
header("Location:index.php");
}
echo $_SESSION['table'];
$tab = $_SESSION['table'];
$sql1 = mysql_query( "show columns from $tab");

$num=mysql_num_rows($sql1);

/*for ($i=1; $i<=$num; $i++)
{
if
}*/
$i=0;
while($row = mysql_fetch_array($sql1))
{
if($_SESSION['table']!='employee' || ($_SESSION['table']=='employee' && $row['Field']!='Sex'))
{
//echo $_POST[$row['Field']] ."</br>";
if(!empty($_POST[$row['Field']]))
{
$i=$i+1;
//echo "hey..". $i. " ". $_POST['$row[\'Field\']'];
}
else
{
$_SESSION['valid']=-1;
$_GET['tablename']=$_SESSION['table'];
//echo "hey";
//header("Location:insert.php");
break;
}
}
}
if($_SESSION['table']=='employee')
{
$num=$num-1;
}

if($i==$num)
{
$i=0;
if($tab == 'employee')
{
$r=mysql_query("select * from employee where Ssn=$_POST[Ssn]");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("INSERT INTO employee(F_name,M_name,L_name,Ssn,Sex,Date_of_employee,D_name,Office_name,Address) 
VALUES('$_POST[F_name]', '$_POST[M_name]' , '$_POST[L_name]' , '$_POST[Ssn]', '$_POST[sex]', '$_POST[Date_of_employee]','$_POST[D_name]','$_POST[Office_name]','$_POST[Address]')");
}
}
else if($tab == 'customer')
{
$r=mysql_query("select * from customer where Customer_id=$_POST[Customer_id] ");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{

if(mysql_query("insert into customer(Customer_id,Name,Contact_no,Address) values ('$_POST[Customer_id]','$_POST[Name]','$_POST[Contact_no]','$_POST[Address]')")){
echo ":)";
}
else{
echo ":(";
}
}
}
else if($tab == 'field')
{
$r=mysql_query("select * from field where Location='$_POST[Location]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into field(Location, Size, Vegetation, Cust_num) values ('$_POST[Location]','$_POST[Size]','$_POST[Vegetation]','$_POST[Cust_num]')");
}
}
else if($tab == 'manufacturing company')
{
$r=mysql_query("select * from manufacturing company where Name='$_POST[Name]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into has(Name, Address, Contact_no, Office_name) values ('$_POST[Name]','$_POST[Address]','$_POST[Contact_no]','$_POST[Office_name]')");
}
}
else if($tab == 'resource')
{
$r=mysql_query("select * from resource where name='$_POST[name]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into resource(name, nature, avalability) values ('$_POST[name]','$_POST[nature]','$_POST[avalability]')");
}
}
else if($tab == 'transport1')
{
$r=mysql_query("select * from transport1 where location='$_POST[location]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into transport1(name_of_company, location, vehicle) values ('$_POST[name_of_company]','$_POST[location]','$_POST[vehicle]')");
}
}
else if($tab == 'transport2')
{
$r=mysql_query("select * from transport2 where Location='$_POST[Location]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into transport2(Location, vehicle, charges) values ('$_POST[Location]','$_POST[vehicle]','$_POST[charges]')");
}
}
else if($tab == 'provides')
{
$r=mysql_query("select * from provides where Essn='$_POST[Essn]' and Name='$_POST[Name]'");
$num_rows = mysql_num_rows($r);
if ($num_rows)
{
echo "record already exists..enter new values";
unset ($r);
}
else
{
mysql_query("insert into provides(Essn, Name, Date_of_order, Date_of_delivery) values ('$_POST[Essn]','$_POST[Name]','$_POST[Date_of_order]','$_POST[Date_of_delivery]')");
}
}
//header("Location:index.php");
}
?>
</html>

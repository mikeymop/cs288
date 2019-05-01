<html>
<head>
    <title>SQL SELECT Statement</title>
</head>
<style>
  table { font-family: OpenSans-Regular, Sans; margin: center; border-collapse: collapse; border: 0px solid transparent; border-spacing: 1; border-radius: 10px; background: #36304a; }
  th { background: #36304a; border-radius: 10px; border: 0px solid transparent; overflow: hidden; line-height: 1.2 font-size: 15px; padding: 4px; }
  th a { padding: 4px; color: #fff; }
  tr {background: white; border: 0px solid transparent; }
  tr:hover { color: #555555; background-color: #f5f5f5; cursor: pointer; }
  td { padding: 4px; border: 1px solid; }
  h1 { font-family: OpenSans-Regular, Sans; }
</style>
<body>
<h1 align="center">NASDAQ's Most Active Stocks</h1>
<table align="center" border="1">
    <tr>
        <!-- inject php ternary in <a> for asc/desc switch -->
        <th><a href="index.php?s=rank&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Rank</a></th>
        <th><a href="index.php?s=exchange&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Exchange</a></th>
        <th><a href="index.php?s=symbol&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Symbol</a></th>
        <th><a href="index.php?s=company&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Company</a></th>
        <th><a href="index.php?s=volume&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Volume</a></th>
        <th><a href="index.php?s=price&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">Price</a></th>
        <th><a href="index.php?s=chng&ad=<?php echo ($_GET['ad']=='asc')? 'desc' : 'asc'; ?>">%Change</a></th>
    </tr>
<?php
    $cnx = new mysqli('sql.njit.edu', 'md537', 'freshen77', 'md537');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM stocks';
    // append the sql select string with sort queries
    $sortparam = $_GET['s'];
    $ascdesc = ($_GET['ad']=='asc')? 'ASC' : 'DESC'; //get the query string for sql order
    // avoid case stmt by checking if sortparam is empty
    if(!empty($sortparam))
        $query .= " ORDER BY (".$sortparam.") ".$ascdesc."";

    $cursor = $cnx->query($query);
    while ($row = $cursor->fetch_assoc()) {
        echo '<tr>';
        echo '<td>' . $row['rank'] . '</td>
              <td>' . $row['exchange'] . '</td>
              <td>' . $row['symbol'] . '</td>
              <td>' . $row['company'] . '</td>
              <td>' . $row['volume'] . '</td>
              <td>' . $row['price'] . '</td>
              <td align="right">' . $row['chng'] .'</td>';
        echo '</tr>';
    }
    $cnx->close();
?>
</table>
</body>
</html>
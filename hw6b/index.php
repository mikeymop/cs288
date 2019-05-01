<html>
<head>
    <title>SQL SELECT Statement</title>
</head>
<body>
<h1 align="center">NASDAQ's Most Active Stocks</h1>
<table align="center" border="1">
    <tr>
        <td>Rank</td>
        <td>Exchange</td>
        <td>Symbol</td>
        <td>Company</td>
        <td>Volume</td>
        <td>Price</td>
        <td>%Change</td>
    </tr>
<?php
    $cnx = new mysqli('sql.njit.edu', 'md537', 'freshen77', 'md537');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM stocks';
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
<html>
<head>
    <title>SQL SELECT Statement</title>
</head>
<body>
<h1 align="center">NASDAQ's Most Active Stocks</h1>
<table align="center" border="1">
    <tr>
        <th><a href="index.php?s=rank">Rank</a></th>
        <th><a href="index.php?s=exchange">Exchange</a></th>
        <th><a href="index.php?s=symbol">Symbol</a></th>
        <th><a href="index.php?s=company">Company</a></th>
        <th><a href="index.php?s=volume">Volume</a></th>
        <th><a href="index.php?s=price">Price</a></th>
        <th><a href="index.php?s=change">%Change</a></th>
    </tr>
<?php
    $cnx = new mysqli('sql.njit.edu', 'md537', 'freshen77', 'md537');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM stocks';
    // append the sql select string with sort queries
    $sortparam = $_GET['s'];

    switch (true) {
        case stristr($sortparam,'exchange'):
            $query .= " ORDER BY (exchange)";
            break;
        case stristr($sortparam,'symbol'):
            $query .= " ORDER BY (symbol)";
            break;
        case stristr($sortparam,'company'):
            $query .= " ORDER BY (company)";
            break;
        case stristr($sortparam,'volume'):
            $query .= " ORDER BY (volume)";
            break;
        case stristr($sortparam,'price'):
            $query .= " ORDER BY (price)";
            break;
        case stristr($sortparam,'change'):
            $query .= " ORDER BY (chng)"; //change is a sql kw
            break;
    }
    
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
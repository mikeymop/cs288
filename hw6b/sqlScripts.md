### Create table

```sql
CREATE TABLE stocks (
    rank int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    exchange varchar(6),
    symbol varchar(6),
    company varchar(250),
    volume integer,
    price decimal(5,2),
    chng decimal(4,2)
);
```

### Alter Columns
```sql
ALTER TABLE  stocks
CHANGE price price decimal(5,2);
```
### Sample input statement
```sql
INSERT INTO stocks(exchange, symbol, company, volume, price, chng)
VALUES ('nasdaq', 'INTC','Intel',71500381, 52.43, -5.18);
```

### Sample update
```sql
UPDATE table
SET 
    column1 = new_value1,
    column2 = new_value2,
    ...
WHERE
    condition;
```

### Sample Sort Statement
```sql
select * from stocks
order by (volume) desc;
```

### Better statements
```sql
INSERT INTO stocks(rank, exchange, symbol, company, volume, price, chng)
VALUES (1, 'nasdaq', 'AMD','Advanced Micro Devices',71500381, 12.48, -01.12)
ON DUPLICATE KEY UPDATE 
rank = 2, exchange='nasdaq', symbol='AMD', company='Advanced Micro Devices',volume=71500380, price=12.48,chng=-01.12;

INSERT INTO stocks(rank, exchange, symbol, company, volume, price, chng)
VALUES (1, 'nasdaq', 'AMD','Advanced Micro Devices',71500381, 12.48, -01.12)
ON DUPLICATE KEY UPDATE 
rank = 2, exchange='nasdaq', symbol='AMD', company='Advanced Micro Devices',volume=71500380, price=12.48,chng=-01.12;

Update stocks
set 
    exchange = 'nasdaq',
    symbol = 'INTC',
    company = 'Intel',
    volume = 71500381, 
    price = 52.43,
    chng = -0.99
where
     rank = 1;
```
### PHP Tricks
Ternary Operators
```php
<?php echo (($_GET['ad']=='asc')? 'desc' : 'asc';)?>
```


### Notes

* [Passing Query Strings in HTML Tags with PHP](https://stackoverflow.com/questions/45628071/html-table-php-mysql-toggle-mysql-sorting-order-asc-desc-on-column-header-click)
* [Bash on button press HTML](https://stackoverflow.com/questions/6235785/run-a-shell-script-with-an-html-button)
* [MYSQL Insert On Duplicate](https://dev.mysql.com/doc/refman/8.0/en/insert-on-duplicate.html)
* [Testing Env](https://www.db-fiddle.com/f/ksfY8h7c2KwDp15PEXmPXo/3)
* [Delete/Update SQL](https://www.guru99.com/delete-and-update.html)
* [MySQL Python Docs](https://dev.mysql.com/doc/connector-python/en/connector-python-api-mysqlcursor-execute.html)

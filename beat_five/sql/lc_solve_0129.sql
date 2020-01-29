--lc183
-- 某网站包含两个表，Customers 表和 Orders 表。编写一个 SQL 查询，找出所有从不订购任何东西的客户。
select
    Name as Customers
from
    Customers
where
    Id not in (
        select
            distinct CustomerId
        from
            Orders
    )

--lc184部门工资最高的员工
select
    Department.Name as Department,
    Employee.Name as Employee,
    Employee.Salary as Salary
from
    Employee
    join
    Department
    on Employee.DepartmentId = Department.Id 
where
    (Employee.DepartmentId, Employee.Salary) in 
    (
        select
            DepartmentId,
            max(Salary)
        from
            Employee
        group by 
            DepartmentId
    )

--lc177 第N高的薪水
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  RETURN (
        -- 1.判断n是否大于employee去重后salary的数量，若大于则返回null
        -- 2.先对employee去重降序排列再截取前n位，之后与该数据再取最小值
        select
            if (n > count(distinct Salary), null, 
                (
                    select
                        min(t.Salary)
                    from
                    (
                        select
                            distinct Salary as Salary
                        from
                            Employee
                        order by
                            Salary desc
                        limit
                            n
                    )as t
                )
            )
        from
            Employee
  );
END

--lc181 超过经理收入的员工 
select
    emp.Name as Employee
from
    Employee as emp
    join
    Employee as man
    on emp.ManagerId = man.Id
where
    emp.Salary > man.Salary

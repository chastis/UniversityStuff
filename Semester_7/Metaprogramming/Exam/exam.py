import typing
from functools import wraps 

def attribute_change_logger(impl):
    @wraps(impl)
    def wrapper(descriptor, instance, value):
        if descriptor.var_type == 'money' or \
            descriptor.var_type == 'id':
            with open("changes_in_{}".format(descriptor.name), 'a+') as file:
                try:
                    file.write("{}->{}\n".format(instance.__dict__[descriptor.name], value))
                except KeyError:
                    file.write("None->{}\n".format(value))
        impl(descriptor, instance, value)
    return wrapper

class BancAccountDescriptor:
    def __init__(self, name, var_type = None):
        self.name = name
        if var_type is None:
            self.var_type = name
        else:
            self.var_type = var_type

    def __get__(self, instance, owner):
        if self.name in instance.__dict__.keys():
            return instance.__dict__[self.name]
        else:
            return str(instance.__class__.__name__) + ' object does not currently have {} attribute'.format(self.name)

    @attribute_change_logger
    def __set__(self, instance, value):
        if self.var_type == 'name' and type(value) != str and value.istitle():
            raise ValueError("Name should be an titled")
        elif self.var_type == "money" and type(value) != float and type(value) != int:
            raise ValueError("Money should be a numeric")
        elif self.var_type == "id" and type(value) != int:
            raise ValueError("Id should be an integer")
        elif self.var_type == "currency" and value != 'UAH' and value != 'USD' and value != 'EUR':
            raise ValueError("Only UAH USD and EUR supported currency")
        instance.__dict__[self.name] = value

    def __delete__(self, instance):
        if self.name in instance.__dict__.keys():
            del instance.__dict__[self.name]

class FixedNumCreator(type):
    max_num = 10
    def __init__(cls, *args, **kwargs):
        cls.__instance = []
        super().__init__(*args, **kwargs)
    def __call__(cls, *args, **kwargs):
        if (len(cls.__instance) > FixedNumCreator.max_num):
            return cls.__instance[-1]
        else:
            cls.__instance.append(super().__call__(*args, **kwargs))
            created = cls.__instance[-1]
            with open('metalog.html', 'a+') as f:
                f.write('<head>\n<title> BancAccout </title>\n</head>\n')
                f.write('<body>\n<table border="3px">')
                f.write('<tr><th>Name</th><th>Surname</th><th>Account ID</th><th>Currency</th><th>Money</th><th>Month Payment</th>')
                f.write('<tr>')
                f.write('<td>' + str(created.name) + '</td>\n')
                f.write('<td>' + str(created.surname) + '</td>\n')
                f.write('<td>' + str(created.id) + '</td>\n')
                f.write('<td>' + str(created.currency) + '</td>\n')
                f.write('<td>' + str(created.money) + '</td>\n')
                f.write('<td>' + str(created.month_payment) + '</td>\n')
                f.write('</tr>')
                f.write('</table>\n</body>\n')
        return cls.__instance[-1]
    

class BancAccount(metaclass = FixedNumCreator):
    name = BancAccountDescriptor('name')
    surname = BancAccountDescriptor('surname', 'name')
    currency = BancAccountDescriptor('currency')
    money = BancAccountDescriptor('money')
    month_payment = BancAccountDescriptor('month_payment', 'money')
    id = BancAccountDescriptor('id')
    def __init__(self, name, surname, cur, mon, mon_pay):
        self.name = name
        self.surname = surname
        self.currency = cur
        self.money = mon
        self.month_payment = mon_pay
        self.id = id(self)
    

b = BancAccount('Maksym', 'Shatokhin', 'EUR', 42.0, 37)
print (b.__dict__)
b.money = 37
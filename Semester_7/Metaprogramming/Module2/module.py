import typing

def attr_change_logger(func):
    def decorator(*args):
        decorator.calls += 1
        # args[2] because this works for setters and in setter we have 3 parameters,
        # and we retrieve the third one, 'value'
        with open( str(func.__name__) + str(args[1].__class__.__name__), 'a+') as file:
            file.write("{}\n".format(str(args[2])))

    decorator.calls = 0
    return decorator

class Currency:
    @staticmethod
    def _is_correct_type(currency):
        if currency != 'uah' and currency != 'usd' and currency != 'eur':
            raise Exception("not supported type")
            return False
        return True
    def __init__(self, currency):
        if self._is_correct_type(currency):
            self.currency = currency
    @staticmethod
    def has_attribute(attribute, instance):
        if attribute in instance.__dict__.keys():
            return True
        else:
            return False
    def __get__(self, instance, owner):
        if self.has_attribute(self.currency, instance):
            return instance.__dict__[self.currency]
        else:
            return ' object currently has no attribute ' + str(self.currency)
    def __set__(self, instance, value):
        if self._is_correct_type(value):
            instance.__dict__[self.currency] = value
    def __delete__(self, instance):
        if self.has_attribute(self.currency, instance):
            del instance.__dict__[self.currency]

class NameParam:
    @staticmethod
    def _is_correct_type(name):
        if not isinstance(name, str):
            raise Exception("not supported type")
            return False
        return True
    def __init__(self, name):
        if self._is_correct_type(name):
            self.name = name
    @staticmethod
    def has_attribute(attribute, instance):
        if attribute in instance.__dict__.keys():
            return True
        else:
            return False
    def __get__(self, instance, owner):
        if self.has_attribute(self.name, instance):
            return instance.__dict__[self.name]
        else:
            return ' object currently has no attribute ' + str(self.name)
    def __set__(self, instance, value):
        if self._is_correct_type(value):
            instance.__dict__[self.name] = value
    def __delete__(self, instance):
        if self.has_attribute(self.name, instance):
            del instance.__dict__[self.name]

class NumericParam:
    @staticmethod
    def _is_correct_type(value):
        if not isinstance(value, float):
            raise Exception("not supported type")
            return False
        return True
    def __init__(self, value):
        if self._is_correct_type(value):
            self.value = value
    @staticmethod
    def has_attribute(attribute, instance):
        if attribute in instance.__dict__.keys():
            return True
        else:
            return False
    def __get__(self, instance, owner):
        if self.has_attribute(self.value, instance):
            return instance.__dict__[self.value]
        else:
            return ' object currently has no attribute ' + str(self.value)
    @attr_change_logger
    def __set__(self, instance, value):
        if self._is_correct_type(value):
            instance.__dict__[self.value] = value
    def __delete__(self, instance):
        if self.has_attribute(self.value, instance):
            del instance.__dict__[self.value]

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
            with open("logged.meta", 'a+') as file:
                file.write("{0} added class {1}".format(str(len(cls.__instance)), str(cls.__instance[-1])))
        return cls.__instance[-1]
    

class BancAccount(metaclass = FixedNumCreator):
    name = NameParam('name')
    cur = Currency('uah')
    val = NumericParam(0.0)
    def __init__(self, name, cur, val):
        self.name = name
        self.cur = cur
        self.val = val
    

b = BancAccount('Shatokhin', 'eur', 42.0)
print(b.name)
print(b.cur)
print(b.val)

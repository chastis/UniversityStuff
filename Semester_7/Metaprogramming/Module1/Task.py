from enum import Enum

class BookType(Enum):
    NONE = 0
    FICTION_BOOK = 1
    DICTIONARY = 2
    SCIENCE_MONOGRAPHY = 3
    SCHOOL_BOOK = 4
    MANUAL = 5
    AUDIOBOOK = 6
    JOURNAL = 7
    JOURNAL_SCIENCE_POPULAR = 8
    JOURNAL_SCIENCE = 9
    MAGAZINE = 10

class BookBase:
    book_type = BookType.NONE
    id = 0
    def _set_id_and_type(self):
        if isinstance(type, BookType):
            self.id = type.value
            self.book_type = type
    def __init__(self, type):
        self._set_id_and_type(type)
    @property
    def name(self):
        return getattr(self, "_name")
    @name.setter
    def name(self, name):
        setattr(self, "_name", name) 
    def check_type(self, type):
        if isinstance(type, BookType):
            if self.book_type == type:
                return True
            elif (hasattr(super, "check_type")):
                return super.check_type(type)
        return False
    @staticmethod
    def is_subclass(sub, parent) -> bool:
        return issubclass(sub, parent)
    @staticmethod
    def get_all_subclasses(cls):
        all_subclasses = []
        for subclass in cls.__subclasses__():
            all_subclasses.append(subclass)
            all_subclasses.extend(get_all_subclasses(subclass))
        return all_subclasses

class FictonBook(BookBase):
    pass

class Dictionary(BookBase):
    pass

class ScienceMonography(BookBase):
    pass

class SchoolBook(BookBase):
    pass

class Manual(BookBase):
    pass

class Audiobook(BookBase):
    pass

class Journal(BookBase):
    pass

class ScientificJournal(Journal):
    pass

class PopularJournal(Journal):
    pass

class Magazine(BookBase):
    pass

def get_all_subclasses(cls):
    all_subclasses = []
    for subclass in cls.__subclasses__():
        all_subclasses.append(subclass)
        all_subclasses.extend(get_all_subclasses(subclass))
    return all_subclasses

def get_all_parents(cls):
    return cls.__mro__



f = FictonBook(BookType.FICTION_BOOK)
print(f.id)
print(f.book_type)

f.name = 'Alphabet'
print(f.name)
print(get_all_subclasses(BookBase))
print('\n')
print(get_all_parents(ScientificJournal))
#print(f.check_type(BookType.Journal))

"""    def set_autors(self, autors):
        self.autors = autors
    def get_autors(self):
        if hasattr(self, "autors"):
            return self.autors
        return None
    def set_year_public(self, year_public):
        self.year_public = year_public
    def get_year_public(self):
        if hasattr(self, "year_public"):
            return self.year_public
        return None

    
    def set_num_pages(self, num_pages):
        self.num_pages = num_pages
    def get_num_pages(self):
        if hasattr(self, "num_pages"):
            return self.num_pages
        return None

    def get_attr(self, attr):
        return getattr(self, attr)
    def set_attr(self, attr, value = None):
        setattr(self, attr, value)"""
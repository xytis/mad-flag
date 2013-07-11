Reinventing flags
============

Preferred usage:

    ::
        
        object.set(visible, !update);

        auto flags = object.get();
        flags += visible;
        flags -= update;
        object.set(flags);

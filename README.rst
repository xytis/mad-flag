Reinventing flags
============

Preferred usage:

    ::
        
        object.set(visible, !update);

        auto flags = object.get();
        flags += visible;
        flags -= update;
        object.set(flags);


.. image:: https://d2weczhvl823v0.cloudfront.net/xytis/mad-flag/trend.png
   :alt: Bitdeli badge
   :target: https://bitdeli.com/free


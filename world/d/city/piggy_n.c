inherit __DIR__"piggy.c";

void create()
{
    ::create();

    set ("short", "������");
    set("exits", ([
        "south": __DIR__"club3",
    ]) );
}

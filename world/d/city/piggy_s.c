inherit __DIR__"piggy.c";

void create()
{
    ::create();

    set ("short", "�����Ϸ�");
    set("exits", ([
        "north": __DIR__"club3",
    ]) );
}

inherit ROOM;

/*string* books = ({
        "daodejing-i",
        "daodejing-i2",
        "daodejing-i3",
});*/

void create()
{
        set("short", "��¥");
        set("long", @LONG
��������ɽ�ľ�����ɽ�书�����ڶ���
�������Բ�û��ʲô̫��Ĺż���������ͯ��
�еĲ��������
LONG
        );

        set("exits", ([
                "west" : __DIR__"square",
        ]));

        set("objects", ([
                __DIR__"npc/jiantong" : 1,
//              __DIR__"obj/"+books[random(sizeof(books))] : 1,
                __DIR__"obj/yijing" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

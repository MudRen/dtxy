// create by snowcat jan 21 1998


inherit ROOM;

void create ()
{
  set ("short", "��ٵ�");
  set ("long", @LONG

һ��������ֱ�Ĵ�ٵ���ƽԭ���ɶ�����ԶԶ�����ӿ�������
��ƽ�����ݵ���ʮ���ۡ���ٵ�������ͨ��Զ��������ԶԶ
�ɿ�������Ǹ���

LONG);

  set("exits", ([
        "west" : __DIR__"east4",
        "east" : __DIR__"chengmen",
      ]));
  set("outdoors", __DIR__);

  set("objects", ([ "/d/obj/weapon/throwing/shi.c" : 1, ]));
  setup();
}



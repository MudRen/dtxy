
inherit ROOM;

void create ()
{
  set ("short", "ɽ��");
  set ("long", @LONG

    ʯ����С������ǽ��һ֧�����΢����⣬�����ܿ�������
һ�У��ڿ�ǽ��һ�Ż�Ƥ������һͷ�ǳ��ʵ������ƺ�˯����
�㣬�����˽���������֪����

LONG);

  set("exits", ([
        "west"   : __DIR__"shidong",
      ]));
  set("objects", ([
        __DIR__"npc/zhu"   : 1,
      ]));

  setup();
}




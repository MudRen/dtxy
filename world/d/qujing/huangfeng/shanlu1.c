//Cracked by Roath
//  ����֮�� ������
//  by happ@YSZZ 2000.4.7
//  /d/qujing/huangfeng/road1.c

inherit ROOM;

void create ()
{
  set ("short", "ɽ·");
  set ("long", @LONG

��Ҫ�߳������ˣ�ֻ��ǰ��������ɽ��ʮ���վ�����ʫд����

   �ߵ���ɽ���������룻�������£�������֣������Ȫ���ʵ��ǻ���
   ��ɽ�߲��ߣ����Ͻ��������⽧�����¼��ظ���

LONG);

  set("exits", ([
        "west"  : __DIR__"shanpo",
        "east"  : __DIR__"road4",
      ]));
  set("outdoors","hfd");
  setup();
}

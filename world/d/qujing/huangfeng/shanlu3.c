//Cracked by Roath
//  ����֮�� ������
//  by happ@YSZZ 2000.4.7
//  /d/qujing/huangfeng/shanlu3.c

inherit ROOM;

void create ()
{
  set ("short", "ɽ·");
  set ("long", @LONG

�ߵ�ɽ·�ϣ�����Զ���Ĵ�ɽ������ô�ɽ���Ǹ��հ���ɽ�����
���ϣ�ɽ·����᫣�·�Ծ���Щ��ʯ��ľ��
LONG);

  set("exits", ([
        "westup"  : __DIR__"shanlu4",
        "eastdown"  : __DIR__"shanlu2",
      ]));
  set("outdoors","hfd");
  setup();
}

// Creat by yanyu 1/1/2000
//by lpg 2000.02.19
inherit ROOM;

int block_cmd();

void create ()
{
  set ("short", "����");
  set ("long", @LONG

�������һ��С�ݣ�����û�г��ڵ����ӣ����������о���������ﻹ����
���ˣ�
LONG);

  set("exits", ([ /* sizeof() == 2 */
]));
  setup();
}

void init()
{   
        if (!wizardp(this_player()))
          add_action("block_cmd","",1);   
}

int block_cmd()
{
       string verb = query_verb();

       if (verb=="say") return 0; //allow say
       if (verb=="look") return 0;
       return 1;
}


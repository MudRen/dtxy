// create by snowcat.c 4/20/1997
// room: /d/eastway/bingma.c

inherit ROOM;

void create ()
{
  set ("short", "����ٸ��");
  set ("long", @LONG

������һ���޴�ı���ٸ���У������������ǧ�������
�������ı���ٸ���гɼ�ʮ·�ݶӣ��·����ڴ�����˷�
��Х�������㲻���������ΰ�ĳ��澪����

LONG);

  set("exits", ([
        "west"       : __DIR__"shihuang",
      ]));
  set("objects", ([ /* sizeof() == 1 */
        __DIR__"obj/bingma" : 9,
      ]));
  set("outdoors", __DIR__);

  setup();
}

void init()
{
        add_action("do_zha", "bomb");
}

int do_zha()
{
        object me, *inv;
        int i,j;
        object exp;
        
        me = this_player();
        j = random(800);

        if( !me->query_temp("mark/ʼ����"))

        return 0;
if(!wizardp(me))  return 0;
        inv = all_inventory(me);
                       for(i=0; i<sizeof(inv); i++)
                {
                                
                        if( (int) inv[i]->query("explosive") )
                                exp = inv[i];
                }
        if( !exp) 
        {
        tell_object(me,"��û�����ڣ�\n");
        return 1;
        }

        message_vision("$N��ȼ�����е�"+exp->name()+"������
һ����ȸ��������ö�Ŀ�Ĺ�âӳ����$N���۾���ֻ����һ��������죢�䣢��ը��
һ����ש����ԭ����߸���������ǿ�ȸɽׯ���ƵĻ������õĿ��������õĻ�ҩ��\n", me, exp);
        if(!me->query("m_success/��ש"))
        {
                me->set("m_success/��ש",1);
                me->add("potential",j+500);
                tell_object (me,"��ʶ��ͼֽ��ը����ש���õ���"+chinese_number(j+500)+"��Ǳ�ܣ�\n");
        }
        destruct(exp);
        tell_object(me, "��שһ�����ɽ���������������������ʲô��\n");
        me->set_temp("mark/ʼ����",0);
                        
        return 1;

}






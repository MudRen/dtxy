// Room: /changan/eastseashore.c

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
void fly_eastsea(object me);
int do_zuo(string arg);
int do_dive();
void reset();


void create ()
{
  set ("short", "����֮��");
  set ("long", @LONG

��ǰ���Ƕ�����ãã���������߼ʡ������ϲ�����ӿ������
�ߵ���ͷ����˷�������Ҫ����һ�и��ڵ����ϵĶ�����Ҳ��
�������·�ľ�ͷ����ǰ�Ĵ󺣶�һ��������˵�ǲ�����Խ�ġ�
�밶��Զ��Ư��һֻľ��(mufa)��
LONG);

  set("objects", ([
   __DIR__"npc/jingwei":1,
  ]));
  set("item_desc", ([ /* sizeof() == 1 */
  "mufa" : "һֻľ�����Լ�����Բľ���ɡ��㲻������(zuo)��ȥ��һ�ԡ�
",
]));
  set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"seashore2",
]));
  set("outdoors", 1);

  setup();
}

void init()
{
    object me;
    me=this_player();

   if ((sizeof(me->query_temp("wzg")))==8)
	   {
       		me->set_temp("baxian_arrive",1);
			remove_call_out("fly_eastsea");
			call_out("fly_eastsea",1,me);
	       return;
	   }

	add_action("do_zuo", "zuo");
    add_action("do_zuo", "sit");
    add_action("do_dive", "dive");
}

void fly_eastsea(object me)
{
	object *baxian;    //�����õ�������һ���жϷ�ʽ,ȷ�� environment �����
	int i;
          baxian = all_inventory(environment(me));
		  for (i = 0;i <sizeof(baxian);i++)
          {
             if(baxian[i]->query("id")=="tieguai li")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="cao guojiu")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="lan caihe")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="han xiangzi")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="han zhongli")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="he xiangu")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="zhang guolao")
				  me->add_temp("baxian_arrive",1);
			  if(baxian[i]->query("id")=="lu dongbin")
				  me->add_temp("baxian_arrive",1);       
		  }
	if( me->query_temp("baxian_arrive")<=8 ) return;
   for (i = 0;i<sizeof(baxian);i++)
	{
	   if (!userp(baxian[i]))
	   {
	   	   destruct(baxian[i]);
	   }
	}
   message_vision("\n\n�����ٴ����������ߣ��·�ص�����Щ�������ǿ��ֵ����ӣ����˵ø�ʩ�ɷ�̤�����Ʋ㣮\n\n"NOR, me);
   me->delete_temp("baxian_arrive");
   me->set("fangcun/panlong_wzg_baxian","done");
   me->start_busy(60);
   me->move("/d/sea/onsea");
   call_out("fly_eastsea1",2,me);
}

void fly_eastsea1(object me)
{
   message_vision(HIC"\n\n\n�ø����ɹ������������壬����Ϸ��գ������ϣ������α̺���һ����̸Ц���ƣ��ò���\n\n"NOR, me);
   call_out("fly_eastsea2",5,me);
}

void fly_eastsea2(object me)
{
   message_vision(HIB"\n��ɫ������������������������δ����\n"NOR, me);
   call_out("finish1",3,me);
}

void finish1(object me)
{
   message_vision(WHT"\n\n\n�Ź���ҡͷ���Ե���" + RANK_D->query_respect(me) + "�������Ҫ����ׯ��ȥ�ˣ�\n\n"NOR, me);
   message_vision(HIY"\n\n���������ֱ�ȭ����" + RANK_D->query_respect(me) + "һ�����⣬������ֻ������л���ˣ�\n\n"NOR, me);
   call_out("finish2",3,me);
}

void finish2(object me)
{
	message_vision(HIM"\n\n���ɹ�΢Ц�Ŷ�$N����" + RANK_D->query_respect(me) + "����������ˣ����ձ��кñ���\n\n"NOR, me);
   message_vision("\n\n���ɺ͵�ͷ�Ƶ���" + RANK_D->query_respect(me) + "ȷ���и�֮�ˣ�\n\n"NOR, me);
   call_out("finish3",3,me);
}

void finish3(object me)
{
	message_vision(HIW"\n\n�������������ȵ���" + RANK_D->query_respect(me) + "���Ұ�����Ը���ҵȵ����л֮����\n\n"NOR, me);
   message_vision(YEL"\n\n�����Ӻ����ѵ���" + RANK_D->query_respect(me) + "�ٱ�һ������֪�����͵������Ӵ�����л" + RANK_D->query_respect(me) + "��\n\n"NOR, me);
   message_vision(YEL"���������ĵ����ڶ��������󴫿���ȥ�������������ض�ʱ�����������ǳ�һɨ���⣮\n\n"NOR, me);
   call_out("finish4",3,me);
}

void finish4(object me)
{
	message_vision(MAG"\n\n�ܹ����ð����������Ӻ��ŵ����߳�����Ӧ�����������ƣ�ǧɽĺѩ��ֻӰ��˭ȥ��\n\n"NOR, me);
   message_vision(HIG"\n\n���������Ц����" + RANK_D->query_respect(me) + "������͸���ˣ�������ڣ�\n\n"NOR, me);
   call_out("finish5",2,me);
}
void finish5(object me)
{
	message_vision(HIC"\n$N��æ���ֻ��������λ������ڣ���ǣ���ǣ�\n\n\n"NOR, me);
   message_vision("˵�꣬���ɱ������������ׯ�۷�ȥ��$NҲ������ͷ�ص��˶������ߣ�\n\n"NOR, me);
   me->start_busy(1);
	me->move("/d/changan/eastseashore");
}
 
void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"mufa")) )
            room = load_object(__DIR__"mufa");
        if( room = find_object(__DIR__"mufa") ) {
            if((int)room->query("zuo_trigger")==0 ) {
                room->set("zuo_trigger", 1);
                set("exits/enter", __DIR__"mufa");
                room->set("exits/out", __FILE__);
                message("vision", "һֻľ���Ӻ���Ư�˹�����\n", this_object() );
                message("vision", "ľ��һ����Ȼ�Ǹ�ǳ�ˡ�\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "ľ����Ư�򰶱ߣ������ӻ������ĵصȵȡ�\n",this_object() );
        }
        else
            message("vision", "ERROR: mufa not found\n", this_object() );
    }
    else 
        message("vision", "ľ���Ѿ������ˣ���ʱ������ȥ��\n",
            this_object() );
}


void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "һ����ͷ������ľ������Ưȥ��\n",
        this_object() );

    if( room = find_object(__DIR__"mufa") )
    {
        room->delete("exits/out");
        message("vision", "��Χ�ǰ�ãã��һƬ�����Ѿ��������κ�½�صļ�����...\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"mufa") )
    {
        room->set("exits/out", __DIR__"aolaiws");
        message("vision", "ľ��һ�𣬸�ǳ�ˡ���Ȼ�ǵ�½���ˣ��Ͻ���ȥ�ɡ�\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"mufa") ) {
        room->delete("exits/out");
        message("vision","һ����ͷ������ľ������Ưȥ��\n", room);
room->set("zuo_trigger", 0);
    }
}

int do_zuo(string arg)
{
    string dir;

    if( (arg=="mufa") || (arg=="ľ��")){ 
        message_vision("$N����������ľ����\n", this_player());
        check_trigger();
        return 1;
    }
    else return notify_fail("��Ҫ����ʲô��\n");
}

int do_dive()
{       object me, zhou;
    object ridee;
        me=this_player();
   ridee=me->ride();



	    if(( !(zhou=present("bishui zhou", me))
		||(string)zhou->query("unit")!="��")
		&& (string)me->query("family/family_name")!="����"
		&& (string)me->query("family/family_name")!="��������")

		return notify_fail("��һ����������ˮ�����\n"+
		  "\n��û�����ͱ���ð�����ֻ�øϽ����ϰ�����\n");
                 if ( me->is_busy() )
                      return notify_fail("��һ����������ˮ�����\n��û�����ͱ���ð�����ֻ�øϽ����ϰ�����\n");
  me->start_busy(1);

   if (ridee && ridee->query("under_water")) {
     message_vision(HIY"$Nһ��$n��ͷ�����˴���Ծ��ˮ�С�\n"NOR,me,ridee);
     ridee->move("/d/sea/under1");
  }

      else  message_vision(HIY "$Nһ����������ˮ�У�Ȼ�󲻼��ˣ�\n" NOR, me);
                me->move("/d/sea/under1");
		message_vision("$NǱ�˹�����\n",me);
                return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"mufa") )
        room->delete("zuo_trigger"); 
}


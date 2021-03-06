#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
int do_read(string arg);

void create()
{
        set_name("八瓣梅花锤", ({ "meihua hammer", "hammer" }) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把分八瓣成梅花状的铜锤，上面刻了些符篆。\n");
                set("value", 5000);
		set("no_sell", 1);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，试了试重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(60);
        setup();
}

void init()
{
 object me = this_object();
  object where = environment();

  if (interactive(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
	me->set("transferred", 1);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }

        add_action("do_read", "read");
}

int do_read(string arg)
{	int gain;
	object me=this_player();
	object ob=this_object();
	
	if(! ob->query("OK_to_STUDY"))
		return notify_fail("你无法从这样东西上学到任何东西。\n");
	if( ob->query("transferred"))
		return notify_fail("你无法从这样东西上学到任何东西。\n");
    	if(environment(me)->query("no_fight") || 
       	environment(me)->query("no_magic") )
          return notify_fail("安全区内禁止练功。\n");

	if( (int)me->query_skill("hammer", 1) >= 60 && !me->query_temp("cfpl/hammer") )
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了。\n");
	if( (int)me->query_skill("spells", 1) < 20)
		return notify_fail("可能是你法术不精，无法领会上面的符咒。\n");

	if( (int)me->query_skill("spells", 1) < (int)me->query_skill("hammer", 1) )
		return notify_fail("可能是你法术领会还不深，暂时还领悟不出更深一层的锤法。\n");

	if( (int)me->query("kee") < 30)
		return notify_fail("你太累了，歇歇再来吧。\n");
	if( (int)me->query("sen") < 30)
		return notify_fail("你太疲劳了，歇歇再来吧。\n");

	gain= (int)me->query_skill("spells", 1)/3 + 1 + random((int)me->query_int());

	me->improve_skill("hammer", gain);
	me->receive_damage("kee", 30);
	me->receive_damage("sen", 30);

	write("你认真揣摩着八瓣梅花锤上的盘龙符影，似乎对「基本锤法」又有所了解。\n");
	tell_room( environment(me), me->name() +"双眼盯着八瓣梅花锤，手里还不知在比划什么。\n", ({me}));
	if( me->query_temp("cfpl/hammer") && random((int)me->query_int()) > 30 )
	{
		me->start_busy(20);
		me->delete_temp("cfpl");
		message_vision(HIC"\n$N仔细揣摩着八瓣梅花锤上的盘龙符影，忽然体内龙神真气生出感应！\n"NOR,me);
		if( base_name(environment(me)) != "/d/sea/inside1" )
		{
			message_vision(HIC"\n$N的脚下突然涌起一股水波，水流过后，$N出现在了龙宫广场！！\n"NOR,me);
			me->move("/d/sea/inside1");
		}
		message_vision(HIC"\n$N置身海底，体内龙神真气更盛！\n"NOR,me);
		message_vision(HIC"\n$N四周海水开始波动不安，忽的一个浪头打来，$N被高高抛起！\n"NOR,me);
		message_vision(HIC"\n$N灵觉顿现，龙神真气急速膨胀，彷佛要破体而出！\n"NOR,me);
		message_vision(HIC"\n$N一声龙吟，身形突然倒转而下，有如流星下坠，其快绝伦，掌中八瓣梅花锤直击而下！\n"NOR,me);
		call_out("finish1",1,me);	
	}
	return 1;
}

void finish1(object me)
{
	message_vision(HIC"\n“砰”的一声巨响，八瓣梅花锤重重击在地上，龙宫广场上碎石飞扬！\n"NOR,me);
	message_vision(HIC"\n整座龙宫剧烈的摇晃，海面上亦激起滔天巨浪！\n"NOR,me);
	message_vision(HIC"\n$N怔怔看着地上大坑，竟不敢相信是自己一击所致！\n"NOR,me);
	call_out("finish2",3,me);	
	return;
}
void finish2(object me)
{
	string str = "/d/sea/npc/long";
	string msg;
	int i;
	object longzi;
	message_vision(HIC"\n龙宫中人，四处躲蹿，一时乱成一团。\n"NOR,me);
	for(i=1;i<10;i++)
	{
		msg = str + i;
		longzi = new(msg);
		longzi->move(environment(me));
	}
	message_vision(HIC"\n突然阵阵水波涌起，龙王九子从中走了出来！！\n"NOR,me);
	message_vision(HIC"\n龙王九子看到地上大坑，竟然一时说不出话来！\n"NOR,me);
	call_out("finish3",3,me);	
	return;
}

void finish3(object me)
{
	string str = "/d/sea/npc/";
	string msg;
	object longzi;
	message_vision(HIC"\n龙宫中人，四处躲蹿，一时乱成一团。\n"NOR,me);
	msg = str + "longpo";
	longzi = new(msg);
	longzi->move(environment(me));
	message_vision(HIC"\n突然一阵水波涌起，龙婆惊惊惶惶从中走了出来！！\n"NOR,me);
	message_vision(HIC"\n龙婆有些惊惶失措：是不是那只猴子又来了？！\n"NOR,me);
	msg = str + "longwang";
	longzi = new(msg);
	longzi->move(environment(me));
	message_vision(HIC"\n突然一阵水波涌起，龙王从中走了出来！！\n"NOR,me);
	message_vision(HIC"\n敖广：谁敢在此扰乱龙宫？！\n"NOR,me);
	call_out("finish4",3,me);	
	return;
}

void finish4(object me)
{
	object mazu;
	message_vision(HIC"\n空中传来妈祖的声音：大家莫要惊惶，此乃我龙宫之喜，你等找人修好广场就此散去吧！\n"NOR,me);
	message_vision(HIC"\n一股水流从$N脚底涌起，将$N送到了大海深处！\n"NOR,me);
	me->set("cfpl_lingwu",1);
	me->move("/d/dntg/donghai/mazeend");
	if(!(mazu = present("ma zu",environment(me))))
	{
		mazu=new("/d/sea/npc/shuishen");
		mazu->move(environment(me));
	}
	mazu->command("pat " + me->query("id"));
	mazu->command("say 你就在此静心领悟（lingwu）吧！");
	me->start_busy(1);
	return;
}
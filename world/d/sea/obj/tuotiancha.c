// gangcha.c

#include <weapon.h>
#include <ansi.h>
inherit FORK;
int do_read(string arg);

void create()
{
        set_name("九股托天叉", ({ "tuotian fork","fork", "cha"}) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 5000);
		set("no_sell", 1);
		set("long", "一根九股盘龙藤扭成的利叉，上面刻了些符篆。\n");
		set("wield_msg", "$N从背后拿出把哗哗做响的铁叉来。\n");
		set("unwield_msg", "$N把$n又放回背后。\n");
                set("material", "iron");
        }
        init_fork(60);
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
{       int gain;
        object me=this_player();
        object ob=this_object();

        if(! ob->query("OK_to_STUDY"))
                return notify_fail("你无法从这样东西上学到任何东西。\n");
        if( ob->query("transferred"))
                return notify_fail("你无法从这样东西上学到任何东西。\n");
    	if(environment(me)->query("no_fight") || 
       	environment(me)->query("no_magic") )
          return notify_fail("安全区内禁止练功。\n");


        if( (int)me->query_skill("fork", 1) >= 80 && ( !me->query_temp("cfpl/fork") || me->query_temp("cfpl/fork") >1 ) )
                return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了。\n");
        if( (int)me->query_skill("spells", 1) < 20)
                return notify_fail("可能是你法术不精，无法领会上面的符咒。\n");

        if( (int)me->query_skill("spells", 1) < (int)me->query_skill("fork", 1) )
                return notify_fail("可能是你法术领会还不深，暂时还领悟不出更深一层的叉法。\n");

        if( (int)me->query("kee") < 30)
                return notify_fail("你太累了，歇歇再来吧。\n");
        if( (int)me->query("sen") < 30)
                return notify_fail("你太疲劳了，歇歇再来吧。\n");
        gain= (int)me->query_skill("spells", 1)/3 + 1 + random((int)me->query_int());

        me->improve_skill("fork", gain);
	me->receive_damage("kee", 30);
	me->receive_damage("sen", 30);

        write("你认真揣摩着九股托天叉上的盘龙符影，似乎对「基本叉法」又有所了解。\n");
        tell_room( environment(me), me->name() +"双眼盯着九股托天叉，手里还不知在比划什么。\n", ({me}));
        if( me->query_temp("cfpl/fork") && random((int)me->query_int()) > 30 )
	{
		me->set_temp("cfpl/fork",2);
		message_vision(HIC"\n$N仔细揣摩着九股托天叉上的盘龙符影，忽然体内龙神真气生出感应！\n"NOR,me);
		message_vision(HIC"\n$N的脚下突然涌起一股水波，水流过后，$N出现在了海底莽林！！\n"NOR,me);
		me->move("/d/sea/maze5");
		message_vision(HIC"\n海底莽林四处暗流汹涌，$N体内龙神真气竟然随着暗流起伏跌宕！\n"NOR,me);
		message_vision(HIC"\n$N默查体内真气，渐有所悟，$N抄起九股托天叉舞了起来！\n"NOR,me);
		message_vision(HIC"\n$N于波涛之中舞叉，越舞越是顺手，渐渐领悟了许多顺刺、逆击、横削、倒劈的道理！\n"NOR,me);
		message_vision(HIC"\n$N到这时方始大悟，顿时领悟了风波十二叉的精妙之处！\n"NOR,me);
	}
        return 1;
}


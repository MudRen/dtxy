// fixed overflow issue by emotion 04/28/2006

#include <skill.h>
#include <ansi.h>

//inherit ITEM;
inherit COMBINED_ITEM;
void create()
{
        set_name("追魂符", ({"find seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","一张画上了符咒的桃符纸，中央有个大大的“追魂”字。
你可将它贴(attach)在某人身上追踪其行迹。\n");
        set("base_unit","张");
        set("unit", "张");
        set("value", 0);
	set("no_put",1);
	set("no_sell",1);
	set("no_give",1);
	}
	 set_amount(1);
	setup();
}

void init()
{
	add_action("do_attach","attach");
}
/*
void destruct_me(object where, object me)
{
        object seal;
        if( seal=new("/obj/paper_seal"))
                seal->move(where);
	message_vision("$N手中的$n突发红光，符咒渐渐淡去不见了。\n",where,me);
        destruct(me);
}
*/
void invocation(object who)
{
	float i,a,b,c;
	object me=this_object();

	a=0.0 + who->query("combat_exp");
	b=0.0 + (int)who->query_skill("spells");
	b=b*b;
	c=0.0 + (int)who->query("mana_factor");
	c=c*c*c;
	i=0.0 + a+b+c;
	me->set("owner_ob",who);
	me->set("owner", who->query("id"));
	me->set("ap",i);
	call_out("disapprear",600, me);
	return;
}
int disappear(object me)
{
	destruct(me);
	return 1;
}
int do_attach(string arg)
{
	object victim;
	object seal=this_object();
	object me=this_player();
	object where=environment(me);

	float ap, dp;
	int a, b;

	if( seal->query("can_not_attach") )
		return notify_fail("什么？\n");
	if( !arg )
                return notify_fail("你想对谁使用追魂符？\n");
        if(!objectp(victim = present(arg, environment(me))))
                return notify_fail("这里没有这个人。\n");
	if( me->query("family/family_name") != "将军府" )
		return notify_fail("你不懂得如何控制追魂符。\n");
	if(me->is_busy())
		return notify_fail("你正忙着呢，无法用追魂符。\n");
        if( !victim->is_character() || victim->is_corpse() )
                return notify_fail("看清楚一点，那并不是活物。\n");
	if( where->query("no_magic"))
		return notify_fail("这里不能祭追魂符。\n");
       if( where->query("no_fight"))
                return notify_fail("这里不能祭追魂符。\n");
	if( (int)me->query("mana") < 100 )
		return notify_fail("你的法力不能控制追魂符。\n");
	if( (int)me->query("sen") < 100 )
                return notify_fail("你的精神不足，很难驾驭追魂符。\n");

	ap= 0.0 + (float)seal->query("ap");
	dp= 0.0 + victim->query("combat_exp");
	dp= dp + (int)victim->query_skill("dodge")*(int)victim->query_kar();

	if( (ap+dp) * random(1000)/1000 > dp/10 ){

	tell_room( environment(me), me->name()+"悄悄地将追魂符贴到"+victim->name()+"背后。\n",({me,victim}));

	a=(int)me->query_kar() * (int)me->query("mana");
	b=(int)victim->query("kar") * (int)victim->query("max_mana");
	if( b > random(a+b) ){
		tell_object( victim, me->name()+"对你稀奇古怪地笑了一下。\n");
	}

	tell_object( me,"你悄悄地将追魂符贴到"+victim->name()+"背后。\n");
	seal->set("can_not_attach",1);
	call_out("report",30,victim);
	seal->move(victim);
	} else {
		message_vision("$N一回头，看到$n正要将追魂符往自己背后贴。\n\n", victim, me);
		message_vision("$N对$n大喝一声：“干什么？”\n", victim, me);

		if( !victim->is_fighting(me) ) {
                if( living(victim) ) {
                        if( userp(victim) ) victim->fight_ob(me);
                        else
                                victim->kill_ob(me);
                	}
                me->kill_ob(victim);
        	}
	}
	me->add("mana",-50);
        add_amount(-1);
        me->start_busy(1+random(2));

	return 1;
}
int report(object who)
{
	object where, owner_ob;

	if( !objectp(owner_ob = query("owner_ob")) ) {
		destruct(this_object());
		return 1;
	}

	if( environment(this_object()) != who ){
		destruct(this_object());
		return 1;
	}
	where=environment(who);

	tell_object(owner_ob, "你模模糊糊听到一个声音："+who->name()+"现在在"+where->query("short")+"。\n");
	owner_ob->receive_damage("sen", 10);
	owner_ob->add("mana",-10);
         add_amount(-1);
	call_out("report", 30, who);
	return 1;
}


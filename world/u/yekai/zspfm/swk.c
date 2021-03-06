// demongorgon.c

#include <ansi.h>

inherit NPC;
string ask_for_zspfm();
void create()
{
	set_name( HIW "孙悟空" NOR, ({ "sun xingzhe","swk","sun","xinzhe" }) );
	set("long",@LONG
他就是曾经大闹天宫的孙大圣了。
曾经跟随唐僧西天取经，历尽千辛万苦，终于修成了正果。你可以问他有关"转世绝学"的消息。
LONG);

	set("age", 30);
          set("title", HIY"斗战胜佛"NOR);
	set("max_gin", 3000);
	set("max_kee", 3000);
	set("max_sen", 3000);

	set("max_atman", 3000);
	set("atman", 3000);
      set("max_force", 5000);
      set("force", 10000);
      set("max_mana", 5000);
      set("mana", 10000);

	set("str", 40);
	set("cor", 40);
	set("cps", 40);
	set("spi", 40);
	set("int", 40);
	set("con", 40);
	set("kar", 40);
	set("per", 10);

	set("combat_exp", 3500000);
	set("daoxing", 2000000);

	set_skill("unarmed", 250+random(50));
        set_skill("dodge", 250+random(50));
        set_skill("parry", 250+random(50));
	set_skill("stick", 250+random(50));
	set_skill("spells", 250+random(50));
	set_skill("dao", 250+random(50));
	set_skill("puti-zhi", 250+random(50));
	set_skill("wuxiangforce", 250+random(50));
	set_skill("force", 250+random(50));
	set_skill("qianjun-bang", 250+random(50));
	set_skill("jindouyun", 250+random(50));
	
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
        set("force_factor",300);	
        set("mana_factor",300);
        set("bellicosity",300);
        set("nk_gain", 100+random(50));
        set("nk_factor", 12);
	/*
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "light" :),
		(: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );
	*/
	set_temp("apply/attack", 200);
	set_temp("apply/defense", 200);
	set_temp("apply/armor", 250);
	set_temp("apply/damage", 250);
	set("inquiry", ([
                "转世绝学" : (: ask_for_zspfm :),
                ]) );
	setup();
}
string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"你已经领悟了足够多的绝学了!\n"NOR;
	if (me->query("zspfm/zspfm_swk"))
		return HIY"我的绝学你已经掌握了！\n"NOR;
	if (me->query("lunhui_zhuanshi") < 4)
		return HIY"四转以上才能领悟我的绝学!\n"NOR;
	if (me->query("zspfm/zspfm_swk_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"你的修为还不够，领悟不到绝学!\n"NOR;
	me->add("zspfm/zspfm_swk_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_swk",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n【转世绝学】：恭喜"+me->query("name")+"在第"+chinese_number(me->query("zspfm/zspfm_swk_number"))+"次的时候领悟了斗战胜佛的绝学！\n"NOR, users() );
		return HIY"恭喜恭喜，你成功领悟了我的绝学!\n"NOR;
	} else {
		return HIY"非常遗憾，你机缘不到，没能领悟我的绝学!\n"NOR;
	}
}


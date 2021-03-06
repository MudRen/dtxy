#include <ansi.h>
#include <zhuanshi.h>
inherit NPC;

string ask_for_zspfm();
void create()
{
        set_name(HIW"白龙马"NOR,({"bailong ma","bailong"}));
        set("gender","男性");
        set("age",40);
        set("per", 40);
        set("int", 30);
        set("kar", 30);
        set("str", 20);
        set("cor", 25);
        set("cps", 99);
        set("long", @LONG
他就是英俊潇洒的小白龙了。
曾经跟随唐僧西天取经，历尽千辛万苦，终于修成了正果。你可以问他有关"转世绝学"的消息。
LONG);
        set("daoxing",1000000);
        set("combat_exp", 12345);
        set("max_force", 5000);
        set("class","bonze");
        set("eff_kee", 5000);
        set("eff_gin", 5000);
        set("eff_sen", 5000);
        set("kee", 5000);
        set("gin", 5000);
        set("sen", 5000);
        set("force", 5000);
        set("mana", 5000);
        set_skill("buddhism", 300);
        set_skill("spells", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("force", 40);
        set_skill("unarmed", 40);
        
        set("title", HIY "八部天龙" NOR);
        set("attitude", "friendly");
		/*
       set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :)
        }));
		*/
		set("inquiry", ([
                "转世绝学" : (: ask_for_zspfm :),
                ]) );
        setup();
}

string ask_for_zspfm() {
	object me=this_player();
	if (me->query("zspfm/number")>=2)
		return HIY"你已经领悟了足够多的绝学了!\n"NOR;
	if (me->query("zspfm/zspfm_xbl"))
		return HIY"我的绝学你已经掌握了！\n"NOR;
	if (me->query("lunhui_zhuanshi") < 1)
		return HIY"一转以上才能领悟我的绝学!\n"NOR;
	if (me->query("zspfm/zspfm_xbl_number")*20000000 > (me->query("combat_exp")+me->query("daoxing")))
		return HIY"你的修为还不够，领悟不到绝学!\n"NOR;
	me->add("zspfm/zspfm_xbl_number",1);
	if (random(me->query("int")) > 45) {
		me->set("zspfm/zspfm_xbl",1);
		me->add("zspfm/number",1);
		message( "chat", HIY"\n【转世绝学】：恭喜"+me->query("name")+"在第"+chinese_number(me->query("zspfm/zspfm_xbl_number"))+"次的时候领悟了小白龙的绝学！\n"NOR, users() );
		return HIY"恭喜恭喜，你成功领悟了我的绝学!\n"NOR;
	} else {
		return HIY"非常遗憾，你机缘不到，没能领悟我的绝学!\n"NOR;
	}
}

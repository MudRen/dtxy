
inherit NPC;

void create()
{
       set_name("С?к?", ({"kid"}));
       set("gender", "????");
        set("combat_exp", 100);
	set("per", 19);
	set("str", 10);
       set("age", 8);
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("chat_chance", 10);
        set("chat_msg", ({
            "С?к???????????ɵЦ?˼?????\n",
            (: random_move :)
        }) );

        setup();
       add_money("coin", 10+random(50));
}


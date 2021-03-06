
inherit NPC;
void create()
{
  set_name("雷神", ({"lei shen", "leishen", "shen"}));
  set("gender", "男性");
  set("attitude", "friendly");
  set("combat_exp", 3000000);
  set("daoxing", 3000000);

  set("age", 100);
  set("per", 100);
  set("str", 30);
  set("int", 30);
  set("cor", 30);
  set("cps", 30);
  set("con", 30);
  set("max_kee", 6000);
  set("max_sen", 4000);
  set("force", 5000);
  set("max_force", 5000);
  set("max_mana", 3000);
  set("mana",6000);  
  set("mana_factor",200);  
  set("force_factor",200);  
  set_skill("spells", 250);
  set_skill("force", 250);
  set_skill("unarmed", 250);
  set_skill("puti-zhi", 250);
  set_skill("parry", 250);
  set_skill("wuxiangforce", 250);
  set_skill("dao", 250);
  set_skill("dodge", 250);
  set_skill("jindouyun", 250);
  map_skill("dodge", "jindouyun");
  map_skill("unarmed", "puti-zhi");
  map_skill("spells", "dao");
  map_skill("force", "wuxiangforce");
  set("class","xian");

         set("chat_chance_combat", 50);
         set("chat_msg_combat", ({
        (: cast_spell, "thunder" :),
       }));
        set_temp("apply/armor", 300);

  setup();
}

void die()
{
    object rope;
    string rp="/d/zhuxian/obj/zhuxian.c";
    if( !rp->in_mud() )
    {
    	
    		rope = new(rp);
    		message("vision", "一阵红光闪过，雷神消失的无影无踪，地上留下一道红光。\n", environment());
    		rope->move(environment(this_object()));
    	
    }
    else
    {
    	message("vision", "雷神化作一道红光消失的无影无踪。\n", environment());
    }
    destruct(this_object());
}

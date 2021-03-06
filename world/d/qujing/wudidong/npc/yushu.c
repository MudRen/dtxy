
// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// yushu.c, 玉鼠精
// created by mes, updated 6-20-97 pickle
// updated again by pickle on 9-2-97, to open her menpai

/************************************************************/

// declarations and variables

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
   string ask_mieyao();
   string ask_cancel();
string say_key();
string ask_daojian();
void punish_player(object me);
   string ask_swear();
int accept_object(object me, object ob);

/************************************************************/
void create()
{
  set_name("玉鼠精", ({"yu shu","yushu", "shu", "monster"}));
    set_weight(1000000);
  set("gender", "女性" );
  set("age", 23);
  set("long", 
"她就是这无底洞的洞主了。她从修道成人行以来，吃人无数，\n"
"也不知为什么玉皇还未曾派兵来围剿。听说她在天宫有亲，也\n"
"不知真假。\n");
  set("title", "地涌夫人");
  set("combat_exp", 1500000);
  set("attitude", "heroic");
  set("daoxing", 3000000);
  create_family("陷空山无底洞", 1, "弟子");
  set("int", 25+random(5));
  set("cor", 30+random(10));
  set_skill("unarmed", 150);
  set_skill("dodge", 180);
  set_skill("parry", 160);
  set_skill("spells", 160); 
  set_skill("yaofa", 160);
  set_skill("sword",190);
  set_skill("qixiu-jian",190);
  set_skill("blade", 180);
  set_skill("kugu-blade", 200);
  set_skill("lingfu-steps", 150);
  set_skill("yinfeng-zhua", 150);
  set_skill("force", 180);   
  set_skill("huntian-qigong", 180);
  map_skill("force", "huntian-qigong");
  map_skill("spells", "yaofa");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("sword", "qixiu-jian");
  map_skill("parry", "kugu-blade");
  map_skill("blade", "kugu-blade");
  map_skill("dodge", "lingfu-steps");
  set("per", 50);
  set("max_kee", 2500);
  set("max_sen", 2500);
  set("force", 3800);
  set("max_force", 2000);
  set("force_factor", 150);
  set("mana",3000);
  set("max_mana", 3000);
  set("mana_factor", 50);
  set("inquiry",([
 "斗佛" : (: ask_mieyao :),
    "cancel" : (: ask_cancel :),
       "key": (: say_key :),
       "钥匙": (: say_key :),
       "name": "老娘就是这无底洞的开山祖师！",
    //"发誓" : (: ask_swear :),
    "刀剑" : (: ask_daojian :),
       "here": "这里就是陷空山无底洞！就算你调十万天兵来也奈何我不得！",
       "rumors": "老娘刚刚抓住一个和尚。看来马上就有新鲜人肉吃了。",
       "人肉包子": "混帐！饿了不会去找厨子？",
       "和尚": "嘿嘿，眼下正饿着他呢。等他肠子干净了就可以蒸熟了吃了。\n"
          "不过也该派人去看看他了。说不定他已经饿死了。",
       "看看": "要看看也行，就是不知道我把钥匙放哪儿了。",
       ]));
  set("chat_chance_combat", 60);
   
   set("chat_msg_combat", ({
     (: exert_function, "zhangqi" :),
        (: perform_action,"blade", "pozhan" :),
        (: perform_action,"blade", "diyu" :),
   }) );
  setup();
  carry_object("/d/obj/weapon/blade/yanblade")->wield();
  carry_object("/d/obj/cloth/nichang")->wear();
  carry_object("/d/obj/cloth/yuanxiang")->wear();
}
/**************************************************************/
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("没用的东西！");
}
else
{
     return ("你有任务吗？！");
}
}
string ask_mieyao()
{
   object me=this_player();

    if(me->query("family/family_name")!="陷空山无底洞")
      return ("你不是本门中人!");

   command("pat "+me->query("id"));
    command("say 有志气！");
   return "/d/obj/mieyao"->query_yao(me);
}

int attempt_apprentice(object me)
{
  string myname=RANK_D->query_rude(me);
  string myid=me->query("id");
  command("look "+myid);
  command("consider");
  if(me->query("family/master_id") != "tian shu" && me->query("combat_exp") < 200000)
  {
      command("say 什么东西？给我滚！");
      return 1;
  }
  if (me->query("wudidong/sell_reward") < me->query("combat_exp") / 20)
  {
    command("say "+myname+"要想入我门下，先多去弄些人肉来，老娘看你心诚，这拜师就好商量了。");
    return 1;
  }
  if (me->query_skill("huntian-qigong", 1) < 50 && me->query("combat_exp") < 200000)
  {
    command("say "+me->name()+"你个废物！就凭那点本事还不配！");
    return 1;
  }
  command("grin");
  command("say 老娘最爱吃人肉包子了。"+myname+"别忘了多给厨房弄点原料！");
  command("recruit "+myid);
  return 1;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob))
  {
    ob->set("class", "yaomo");
  ob->set("title", YEL"陷空山地涌夫人座下弟子"NOR);
  }
}
/************************************************************/

// the prevent learn series... first yushu tosses the player
// if he's saved the monk, and second she has condition of
// learning kugu-blade.

int prevent_learn(object me, string skill)
{
  int mykugu=me->query_skill("kugu-blade", 1);
  if (wizardp(me) && me->query("env/immortal"))
    return 0;
  if (skill == "kugu-blade")
  {
      if (mykugu>=200)
      {
   command("say 你又用不着我来教！难道是来消遣老娘的？");
   return 1;
      }
      if (mykugu<200 && me->query("wudidong/given_book_3")) return 0;
      if (mykugu<141 && me->query("wudidong/given_book_2")) return 0;
      if (mykugu<=81 && me->query("wudidong/given_book_1")) return 0;
      command("say 不教！此乃无底洞不传之密！");
      return 1;

    }
  if (skill == "yaofa" && me->query("obstacle/wudidong")=="done")
  {
      call_out("punish_player", 1, me);
      return 1;
  }
  return 0;
}
int accept_object(object me, object ob)
{
    int volume;
    if(ob->query("name_recognized") != "枯骨刀秘笈")
        return notify_fail(CYN"玉鼠怒道：混帐，我又不是收破烂的！\n"NOR);
    volume=ob->query("册");
    me->set("wudidong/given_book_"+(string)volume, 1);
    if (me->query("family/master_id") != "yu shu")
   command("say 嗯，果然不错。老娘自当履行诺言，收你为徒！");
    command("recruit "+me->query("id"));
    if (me->query("family/master_id") == "yu shu")
   command("say 好徒弟，果然不枉了师父的一番调教。");
    return 1;
}

void punish_player(object me)
{
    object *inv, ob;
    int i;
    inv=all_inventory(me);
    i=(int)sizeof(inv);
    while(i--)
    {
        ob=present(inv[i],me);
        destruct(ob);
        continue;
    }
    command("say "+me->name()+"你个混帐！叫你去好好看着那老秃驴，你竟敢把他给放跑了！");
    command("say 你好大的胆子！还敢回来跟老娘学本事！");
    command("say 不好好教训教训你，别人还都以为老娘是好欺负的了！");
    message_vision("只见玉鼠左手掐了个决，口中念念有词，对$N喝道：倒！\n", me);
    me->unconcious();
    message_vision("玉鼠精象提小鸡般提起$N，往后一扔。$N不见了！\n", me);
    me->move("/d/qujing/wudidong/punish");
    message("vision", "只听“咚”的一声，$N落了下来！\n", me);
    return;
}
/*********************************************************************/
string say_key()
{
  object me=this_player(), ob, npc=this_object();
  int mykar=me->query_kar();
  int real_key_condition;

  if(npc->is_fighting() || me->is_fighting())
    return ("没门！等着点！");
  if (member_array("tian shu",me->parse_command_id_list())==-1 )
    {
      call_out("killplayer", 1, me);
      return ("哪儿来的"+RANK_D->query_rude(me)+"？找死！");
    }
  message_vision(CYN"玉鼠对$N说：“好吧，拿去。”\n"NOR, me);
  if (npc->query_temp("gave_out_key"))
      real_key_condition=0;
  else real_key_condition=1;
  if (!real_key_condition)
    {
      ob=new("/d/qujing/wudidong/obj/key-fake");
    }
  else if (random(mykar)>8)
    {
      ob=new("/d/qujing/wudidong/obj/key-real");
      npc->set_temp("gave_out_key", 1);
    }
  else ob=new("/d/qujing/wudidong/obj/key-fake");
  ob->move(me);
  me->set_temp("mark/wudidong_yushu_gave_me_key", 1);
  return ("好好看守那秃驴！\n");
}
void killplayer(object me)
{
  this_object()->kill_ob(me);
}
/**************************************************************/
void init()
{
//       add_action("do_swear", "swear");
  object me;

  ::init();
  if( interactive(me = this_player()) && !is_fighting() ) {
    call_out("greeting", 1, me);
  }
}
void greeting(object me)
{
  int myspells=me->query_skill("spells");
  int mykar=me->query_kar();
  string npcname=this_object()->query("name");
  string npcrude=RANK_D->query_self_rude(this_object());
  string myrude=RANK_D->query_rude(me);

  if( !me || environment(me) != environment() ) return;
  if( me->query("family/family_name") == "陷空山无底洞")
    return;
  if( member_array("yu shu", me->parse_command_id_list())!=-1)
    {
      command("say 哪个混账？竟敢变成"+npcrude+"样子招摇撞骗？！找死！");
      kill_ob(me);
      return;
    }
  if( member_array("tian shu",me->parse_command_id_list())==-1 )
    {
      command("say 哪里来的"+myrude+"？无底洞不是你撒野的地方！拿命来！");
      command("kill " + me->query("id"));
      return;
    }
  if( random(mykar) > 8) return;
  else
    {
      message_vision(CYN ""+npcname+"对$N大喝道：呔！什么东西！？休想从"+RANK_D->query_self_rude(this_object())+"眼下溜过去！\n"NOR, me);
      message_vision(npcname+"大喊一声：现！$N顿时现出原形，原来是"+me->query("name")+"！\n", me);
      me->delete_temp("spellslevel");
      me->delete_temp("d_mana");
      me->delete_temp("apply/name");
      me->delete_temp("apply/id");
      me->delete_temp("apply/short");
      me->delete_temp("apply/long"); 
      kill_ob(me);
      return;
    }
}



//int do_swear()
string ask_swear()
{
	object me;
	int amount,i;
	mapping skills;
	string *skillsname;
	me=this_player();
        me->command("say 我愿意效忠夫人，永远做无底洞的好弟子。");
	if (mapp(skills = me->query_skills()))
            {
               skills = me->query_skills();
               skillsname = keys(skills);
               amount = sizeof(skills);
               for (i = 0; i < amount; i++)
                {if (skillsname[i]!="qixiu-jian"
                     && skillsname[i]!="kugu-blade"
                     && skillsname[i]!="yinfeng-zhua"
                     && skillsname[i]!="daya-jian"
                     && skillsname[i]!="yaofa"
                     && skillsname[i]!="huntian-qigong"
                     && skillsname[i]!="blade"
                     && skillsname[i]!="dodge"
                    && skillsname[i]!="lingfu-steps"
                     && skillsname[i]!="stealing"
                     && skillsname[i]!="sword"
                     && skillsname[i]!="parry"
                     && skillsname[i]!="unarmed"
                     && skillsname[i]!="literate"
                     && skillsname[i]!="force"
                     && skillsname[i]!="spells")
                    {command("say 你身怀其他门派的武功，叫我如何信你？"); 
//return 1;}  
return ("你不是本门中人!");
}
                  }
                     command("say 好，希望你能担负起发扬无底洞的重任，为我派争光。");
                     me->delete("betray/count", 1);
                     me->delete("betray/wudidong", 1);
                     me->delete("betrayer", 1);
                     me->set("maximum_force",me->query("max_force"));
            }        
return ("好好努力!");
}    

string ask_daojian()
{
	object me = this_player();
	object ts,swk,zbj,shs,lijing,nezha;
	if( !wizardp(me) && me->query("family/family_name") != "陷空山无底洞" )	
		return ("你不是我陷空山无底洞弟子！");
	if( me->query("betray/count") )
		return ("你三心二意无法领会刀剑绝学。\n");
	if( me->query("daojian_known") > 2 )
		return ("刀剑绝学，你都已经学会了啊！");
	if( me->query("daojian_cant") )
		return ("该学的你都学过了，不该学的，你也领会不了，莫要强求！");
	if( me->query_skill("literate",1) < 200 )
		return ("就你这点学识，如何能学会刀剑绝学？");
	if( me->query_skill("yinfeng-zhua",1) < 200 )
		return ("就你这点拳脚功夫，如何能学会刀剑绝学？");
	if( me->query_skill("kugu-blade",1) < 200 )
		return ("就你这点刀法，如何能学会刀剑绝学？");
	if( me->query_skill("qixiu-jian",1) < 200 )
		return ("就你这点剑法，如何能学会刀剑绝学？");
	if( me->query_skill("huntian-qigong",1) < 200 )
		return ("就你这点内功，如何能学会刀剑绝学？");
	if( !me->query("daojian_known") )
	{
		if( !me->query_temp("daojian/zbj") )
		{
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：徒弟们，这一望无际的平野，竟不见一道炊烟，不知道有没有妖怪呀？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：师傅，这还不简单，让八戒去查探一番，不就知道到了吗？嘿嘿...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"八戒"+NOR"：哼，这种事又轮到我头上来了...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：呆子，又想偷懒？要不让沙师弟去查探，你来挑行李？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"沙僧"+NOR"：唉，大师兄这到不必，师傅，你们稍事休息，我去去就来。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：悟净，你终日劳累，还是休息一下吧，悟能，你快去查探一番，快去快回，莫要误了行程。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"八戒"+NOR"：你们...，师傅，哪我先去了...\n"NOR,users());
			me->set_temp("daojian/zbj","begin");
			zbj = new("/d/qujing/wudidong/npc/zbj.c");
			zbj->set("owner",me);
			zbj->move("/d/qujing/wudidong/firemount-wudidong2");
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"八戒"+NOR"：前面刚好有个小山头，我去看看。\n"NOR,users());
			return ("听说唐僧师徒来到了张家村，猪八戒正在探路，你去给我把他抓回来！！！");
		}
		else if( me->query_temp("daojian/zbj") == "begin" )
		{
			return ("还不快去抓猪八戒？！");
		}
		else if( me->query_temp("daojian/zbj") == "done" && !me->query_temp("daojian/ts") )
		{
			me->set_temp("daojian/ts","begin");
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：悟空，八戒去了这么久，怎么还没回来，不会遇到妖怪了吧？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：师傅，我看这附近妖气不重，八戒定能对付得了，您就别着急了。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：悟空，你怎么能这样对待师弟，快去看看，降伏了妖怪，我们也好早点赶路！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+me->name()+"，做得好，你再去帮我引开孙悟空，我亲自出马，将唐僧抓回洞府。！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+me->name()+NOR"：是，夫人！"+me->name()+"使了个土遁，来到了小山头上！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：不好，好重的妖气，沙师弟，你看好师傅，我去去就来！\n"NOR,users());
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/firemount-wudidong2");
			me->move("/d/qujing/wudidong/firemount-wudidong2");
			return ("拜托了！");
		}
		else if( me->query_temp("daojian/zbj") == "done" && me->query_temp("daojian/ts") == "begin" )
		{
			return ("还不快去引开孙悟空？等我得手以后，你可以趁机逃走！");
		}
		else if( me->query_temp("daojian/zbj") == "done" && me->query_temp("daojian/ts") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 10 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("我能抓到唐僧，你功不可没，我这就传你刀剑第一段的口诀，能不能领悟，就看你的悟性了！");
		}
		else
		{
			return ("没用的东西，还好意思回来见我？！");
		}
	}
	if( me->query("daojian_known") == 1 )
	{
		if( !me->query_temp("daojian/swk") )
		{
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：师傅、师傅、师傅...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：可恶的妖精，狡猾的妖精。土地你给我出来...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"土地"+NOR"：大圣，大圣，招小神来，有什么事情？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：土地，你地界上出了妖精，还把我师傅给抓走了，你可知罪？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"土地"+NOR"：唉，大圣，你有所不知，这妖精法力高强，小神实在不是对手啊。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：哼，又是老一套，你可以知道妖精的洞府所在？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"土地"+NOR"：这地下藏有一座大山，山中有一深洞，因为深不见底，所以唤作“无底洞”，多年前被那妖精占了去。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：我这就去找那妖精，夺回师傅。\n"NOR,users());
			me->set_temp("daojian/swk","begin");
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/dong1");
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：嗯，应该就是这里了！孙悟空一纵身，跳入洞中，足下彩云生万道，身边瑞气护千层。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：哼，这洞门了。“轰隆隆”，孙悟空举起金箍棒，将洞门砸个粉碎。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：妖精，赶紧将我师傅送出来，不然让你好看！！！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"：哎呀，不好了，孙悟空打上门来了，"+me->name()+"，你赶紧帮我去将他赶走！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+me->name()+NOR"：是，夫人！"+me->name()+"使了个土遁，来到了洞门！\n"NOR,users());
			me->move("/d/qujing/wudidong/dong1");
			return ("拜托了！");
		}
		else if( me->query_temp("daojian/swk") == "begin" )
		{
			return ("还不快去将孙悟空赶走？！");
		}
		else if( me->query_temp("daojian/swk") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 16 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("赶走孙悟空，足以证明你能够学习更深的刀剑绝学了，我这就传你刀剑第二段的口诀，能不能领悟，就看你的悟性了！");
		}
		else
		{
			return ("没用的东西，还好意思回来见我？！");
		}
	}
	if( me->query("daojian_known") == 2 )
	{
		if( !me->query_temp("daojian/lijing") )
		{
			me->set_temp("daojian/lijing","begin");
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/dong");
			lijing = new("/d/qujing/wudidong/npc/lijing.c");
			lijing->set("owner",me);
			lijing->move("/d/qujing/wudidong/dong");
			nezha = new("/d/qujing/wudidong/npc/nezha.c");
			nezha->set("owner",me);
			nezha->move("/d/qujing/wudidong/dong");
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：这妖精好生厉害...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"土地"+NOR"：大圣，大圣，小神听说，这妖精好像和李天王有亲！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：“阿嚏”～～～！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"哪吒"+NOR"：父王，您怎么了？！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：好像要有什么大事发生！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：当真？！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"土地"+NOR"：大圣，小神也只是听说，您见到李天王可千万别提起小神的名字呀！！！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：罗嗦，难道俺老孙还是怕事之人？！孙悟空一个筋斗云来到了云楼台！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：李靖～～～，快出来见我，不然我拉你去见玉帝。\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"哪吒"+NOR"：大圣，你怎么有空来到云楼供？！哪吒心下思量：看来真的要出事了！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：大圣，找我何事？！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：李靖，你纵容亲戚下届为妖，捉了我师傅，你可知罪？\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：哼，猴子休得造谣！小心我传天兵天降将你拿下，告你个诽谤之罪！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"哪吒"+NOR"：思考中～～～\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：我还想拉你去见玉帝呢，有本事你就来抓，本想给你留个情面...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：你...，来人哪...\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"哪吒"+NOR"：父王，且慢，当年在陷空山，您好像收了一个义女！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：思考中～～～\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：走，随我见玉帝去！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：哎呀，大圣，你看...，实在对不起，这事年岁太久，我给忘记了！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：算你识相！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"李靖"+NOR"：哪吒三太子，速去准备，与我随同大圣下界降妖！三人架起云雾来到了陷空山！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"：不好了，我义父被孙悟空请来了，"+me->name()+"，我无法出面，你去帮我将他们赶走！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+me->name()+NOR"：是，夫人！"+me->name()+"使了个土遁，来到了山顶！\n"NOR,users());
			me->move("/d/qujing/wudidong/dong");
			return ("拜托了！");
		}
		else if( me->query_temp("daojian/lijing") == "begin" )
		{
			return ("还不快去将孙悟空他们赶走？！");
		}
		else if( me->query_temp("daojian/lijing") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 25 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("赶走李靖等人，足以证明你能够学习更深的刀剑绝学了，我这就传你刀剑第三段的口诀，能不能领悟，就看你的悟性了！");
		}
		else
		{
			return ("没用的东西，还好意思回来见我？！");
		}
	}
	return ("嘿嘿！！！");
}

void finish1( object me )
{
	message_vision(HIB"玉鼠在$N耳边，轻轻念出了一段深奥的口诀。\n" NOR,me);
	message_vision(HIB"$N面露喜色，高兴的抓耳挠腮！\n" NOR,me);
	me->delete_temp("daojian");
	me->add("daojian_known",1);
	if( me->query("daojian_known") == 1 )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我抓住唐僧，学会了"+HIB"[刀剑]"+HIC"绝学！\n\n\n"NOR,users());
	if( me->query("daojian_known") == 2 )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我击退孙悟空，对"+HIB"[刀剑]"+HIC"绝学的领悟更进一步！\n\n\n"NOR,users());
	if( me->query("daojian_known") == 3 )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我击退李靖等人，将"+HIB"[刀剑]"+HIC"绝学练到了登峰造极！\n\n\n"NOR,users());
	return ;
}

void finish2( object me )
{
	message_vision(HIB"玉鼠在$N耳边，轻轻念出了一段深奥的口诀。\n" NOR,me);
	message_vision(HIB"$N眉头紧皱，似乎无法领会！\n" NOR,me);
	me->delete_temp("daojian");
	me->set("daojian_cant",1);
	if( me->query("daojian_known") == 1 )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我击退孙悟空，可惜无法领悟更深的"+HIB"[刀剑]"+HIC"绝学！\n\n\n"NOR,users());
	else if( me->query("daojian_known") == 2 )
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我击退李靖等人，可惜机缘不够，无法领会"+HIB"[刀剑]"+HIC"绝学的最高境界！\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗玉鼠精(yu shu)：" + me->name() + "助我抓住唐僧，可惜与"+HIB"[刀剑]"+HIC"绝学无缘！\n\n\n"NOR,users());
	return ;
}
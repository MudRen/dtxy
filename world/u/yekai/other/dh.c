//wzx 取经NPC 2009.10.20

#include <ansi.h>
inherit NPC;
string huanqu();

void create()
{
        set_name(HIM"瑄瑄"NOR, ({"xuan xuan","xuan"}));
        set("gender", "女性" );
        set("age", 20);
        set("title",HIY"过关机器人"NOR);
        set("long", HIG"\n\n伍子胥的过关机器人\n\n"NOR);
        set("combat_exp", 1000000000);
        set("daoxing", 5000);
        set("attitude", "peaceful");
        set("per", 40);
        set("max_kee", 20000);
        set("max_gin", 20000);
        set("max_sen", 20000);
        set("inquiry", ([
                "换取真经" : (: huanqu :),
                ]) );
        setup();
        carry_object("/d/ourhome/obj/pink_cloth")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void init()
{
        add_action("do_agree", "agree");
}

string huanqu()
{
        object me=this_player();

        //if ((int)me->query("combat_exp") > 10000000 ) //假设三万年道行
{
                command("say 我可以帮你过完取经和大闹天宫，不过你总要意思意思下吧。");
                command("say 你道行很多吗，我最喜欢道行了，你是想给我一些么。");
                return ("你愿意否(agree)？");
        }

        return ("你现在的那点道行，我还瞧不上眼呢，再去历练历练吧。\n");
}

int do_agree(string arg)
{
        object who;
        who=this_player();
        seteuid(getuid());
        
        {
                    //who->add("combat_exp",-8000000);  //假设三万年道行
                            //who->add("daoxing",-8000000);  //假设三万年道行
                who->set("startroom","/d/city/kezhan");
       //取经
       who->set("obstacle/yz","done");
	who->set("obstacle/jilei","done");
	who->set("obstacle/nuerguo","done");
	who->set("obstacle/firemount","done");
	who->set("obstacle/yuhua","done");
	who->set("obstacle/hf","done");
	who->set("obstacle/jindou","done");
	who->set("obstacle/yj","done");
	who->set("obstacle/fengxian","done");
	who->set("obstacle/tongtian","done");
	who->set("obstacle/sc","done");
	who->set("obstacle/yinwu","done");
	who->set("obstacle/jz","done");
	who->set("obstacle/chechi","done");
	who->set("obstacle/qinfa","done");
	who->set("obstacle/huoyun","done");
	who->set("obstacle/wudidong","done");
	who->set("obstacle/wuji","done");
	who->set("obstacle/liuer-mihou","done");
	who->set("obstacle/pingding","done");
	who->set("obstacle/biqiu","done");
	who->set("obstacle/baoxiang","done");
	who->set("obstacle/pansi","done");
	who->set("obstacle/baigudong","done");
	who->set("obstacle/zhuzi","done");
	who->set("obstacle/shushan","done");
	who->set("obstacle/wuzhuang","done");
	who->set("obstacle/xiaoxitian","done");
	who->set("obstacle/shenglingzhu","done");
	//who->set("obstacle/village","done");
	who->set("obstacle/niulang","done");
	who->set("obstacle/jingjiling","done");
	//who->set("obstacle/liusha","done");
	who->set("obstacle/tianzhu","done");
	//who->set("obstacle/huangfeng","done");
	who->set("obstacle/jisaiguo","done");
	who->set("obstacle/dudi","done");
	who->set("obstacle/jinping","done");
          who->set("obstacle/gao","done");
       who->set("obstacle/number",26);

       //九重天
       //who->set("9sky/number",9);
      //dntg
	  who->set("dntg/huaguo","done");
	  who->set("dntg/donghai","done");
	  who->set("dntg/hell","done");
	  who->set("dntg/bmw","done");
	  who->set("dntg/lijing","done");
	  who->set("dntg/pantao","done");
	  who->set("dntg/yaochi","done");
	  who->set("dntg/laojun","done");
	  who->set("dntg/erlang","done");
	  who->set("dntg/bagualu","done");
      who->set("dntg/number",10);
      //冥界
     //who->set("mingjie/number",15);
      //12gong
     //who->set("12gong/number",12);
      

                command("say 好吧");
                  //command("chat  恭喜，"+who->query("name")+"用过关机器人换取了真经。\n");
                command ("heihei");
                  //who->move("/d/city/kezhan");
                who->save();

                return 1;
        }
}




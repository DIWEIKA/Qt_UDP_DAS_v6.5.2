#include "udp_recv.h"

UDP_Recv::UDP_Recv(MainWindow* mainwindow)
{
    mainWindow = mainwindow;

    sockVersion = MAKEWORD(2,2);
    if(WSAStartup(sockVersion, &wsaData) != 0)
    {
        printf("winsock initialization FAILED.");
    }
    echo_socket_WIN = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(echo_socket_WIN == INVALID_SOCKET)
    {
        printf("winsocket error !");
    }
    addr_WIN.sin_family = AF_INET;
    addr_WIN.sin_port = htons(7000);
    addr_WIN.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(echo_socket_WIN, (sockaddr *)&addr_WIN, sizeof(addr_WIN)) == SOCKET_ERROR)
    {
        printf("bind error !");
        closesocket(echo_socket_WIN);
    }
    // set socket buffer size
    int optVal = 0;
    int optLen = sizeof(optVal);
    optVal = 4*1024*100000;
    setsockopt(echo_socket_WIN, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, optLen);

    //预先申请存储空间
    p_echo_net_pack_array.reserve(1024);
    p_echo_net_pack_HEX.reserve(2048);
    //    pack_HEX_32.reserve(32*2048);

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata3 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata4 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata5 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata6 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata7 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata8 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata9 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata10 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata11 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata12 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata13 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata14 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata15 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata16 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata17 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata18 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata19 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata20 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata21 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata22 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata23 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata24 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata25 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata26 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata27 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata28 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata29 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata30 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata31 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata32 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata33 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata34 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata35 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata36 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata37 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata38 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata39 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata40 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata41 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata42 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata43 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata44 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata45 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata46 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata47 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata48 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata49 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata50 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata51 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata52 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata53 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata54 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata55 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata56 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata57 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata58 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata59 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata60 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata61 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata62 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata63 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata64 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata65 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata66 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata67 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata68 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata69 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata70 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata71 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata72 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata73 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata74 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata75 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata76 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata77 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata78 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata79 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata80 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata81 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata82 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata83 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata84 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata85 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata86 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata87 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata88 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata89 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata90 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata91 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata92 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata93 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata94 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata95 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata96 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata97 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata98 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata99 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata100 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata101 = make_shared<CirQueue<unsigned char>>(LenoUDP);


    //init CHdataArray
    CHdataArray[0] =  CHdata2;
    CHdataArray[1] =  CHdata3;
    CHdataArray[2] =  CHdata4;
    CHdataArray[3] =  CHdata5;
    CHdataArray[4] =  CHdata6;
    CHdataArray[5] =  CHdata7;
    CHdataArray[6] =  CHdata8;
    CHdataArray[7] =  CHdata9;
    CHdataArray[8] =  CHdata10;
    CHdataArray[9] =  CHdata11;
    CHdataArray[10] =  CHdata12;
    CHdataArray[11] =  CHdata13;
    CHdataArray[12] =  CHdata14;
    CHdataArray[13] =  CHdata15;
    CHdataArray[14] =  CHdata16;
    CHdataArray[15] =  CHdata17;
    CHdataArray[16] =  CHdata18;
    CHdataArray[17] =  CHdata19;
    CHdataArray[18] =  CHdata20;
    CHdataArray[19] =  CHdata21;
    CHdataArray[20] =  CHdata22;
    CHdataArray[21] =  CHdata23;
    CHdataArray[22] =  CHdata24;
    CHdataArray[23] =  CHdata25;
    CHdataArray[24] =  CHdata26;
    CHdataArray[25] =  CHdata27;
    CHdataArray[26] =  CHdata28;
    CHdataArray[27] =  CHdata29;
    CHdataArray[28] =  CHdata30;
    CHdataArray[29] =  CHdata31;
    CHdataArray[30] =  CHdata32;
    CHdataArray[31] =  CHdata33;
    CHdataArray[32] =  CHdata34;
    CHdataArray[33] =  CHdata35;
    CHdataArray[34] =  CHdata36;
    CHdataArray[35] =  CHdata37;
    CHdataArray[36] =  CHdata38;
    CHdataArray[37] =  CHdata39;
    CHdataArray[38] =  CHdata40;
    CHdataArray[39] =  CHdata41;
    CHdataArray[40] =  CHdata42;
    CHdataArray[41] =  CHdata43;
    CHdataArray[42] =  CHdata44;
    CHdataArray[43] =  CHdata45;
    CHdataArray[44] =  CHdata46;
    CHdataArray[45] =  CHdata47;
    CHdataArray[46] =  CHdata48;
    CHdataArray[47] =  CHdata49;
    CHdataArray[48] =  CHdata50;
    CHdataArray[49] =  CHdata51;
    CHdataArray[50] =  CHdata52;
    CHdataArray[51] =  CHdata53;
    CHdataArray[52] =  CHdata54;
    CHdataArray[53] =  CHdata55;
    CHdataArray[54] =  CHdata56;
    CHdataArray[55] =  CHdata57;
    CHdataArray[56] =  CHdata58;
    CHdataArray[57] =  CHdata59;
    CHdataArray[58] =  CHdata60;
    CHdataArray[59] =  CHdata61;
    CHdataArray[60] =  CHdata62;
    CHdataArray[61] =  CHdata63;
    CHdataArray[62] =  CHdata64;
    CHdataArray[63] =  CHdata65;
    CHdataArray[64] =  CHdata66;
    CHdataArray[65] =  CHdata67;
    CHdataArray[66] =  CHdata68;
    CHdataArray[67] =  CHdata69;
    CHdataArray[68] =  CHdata70;
    CHdataArray[69] =  CHdata71;
    CHdataArray[70] =  CHdata72;
    CHdataArray[71] =  CHdata73;
    CHdataArray[72] =  CHdata74;
    CHdataArray[73] =  CHdata75;
    CHdataArray[74] =  CHdata76;
    CHdataArray[75] =  CHdata77;
    CHdataArray[76] =  CHdata78;
    CHdataArray[77] =  CHdata79;
    CHdataArray[78] =  CHdata80;
    CHdataArray[79] =  CHdata81;
    CHdataArray[80] =  CHdata82;
    CHdataArray[81] =  CHdata83;
    CHdataArray[82] =  CHdata84;
    CHdataArray[83] =  CHdata85;
    CHdataArray[84] =  CHdata86;
    CHdataArray[85] =  CHdata87;
    CHdataArray[86] =  CHdata88;
    CHdataArray[87] =  CHdata89;
    CHdataArray[88] =  CHdata90;
    CHdataArray[89] =  CHdata91;
    CHdataArray[90] =  CHdata92;
    CHdataArray[91] =  CHdata93;
    CHdataArray[92] =  CHdata94;
    CHdataArray[93] =  CHdata95;
    CHdataArray[94] =  CHdata96;
    CHdataArray[95] =  CHdata97;
    CHdataArray[96] =  CHdata98;
    CHdataArray[97] =  CHdata99;
    CHdataArray[98] =  CHdata100;
    CHdataArray[99] =  CHdata101;
}

void UDP_Recv::clearCHdata()
{
    for(int i = 0; i<SaveNumber; i++)
        CHdataArray[i]->clear();
}

void UDP_Recv::run()
{
    while(1)
    {
        isStart = mainWindow->isStart;

        if(isStart){

            isHEX = mainWindow->isHEX;

            net_pack_size = 0;

            if(isHEX){

                lenoRecvHEX = lenoRecv * 2;

                //define a new char[]
                p_echo_net_pack[0] = '\0';

                net_pack_size = recvfrom(echo_socket_WIN, (char*)p_echo_net_pack, lenoRecvHEX, 0, (sockaddr *)&src_addr_WIN, &src_addr_len);

                qDebug()<<"Reciving net_pack_size = "<< net_pack_size <<endl;

                //clear QByteArray
                p_echo_net_pack_array.clear();
                p_echo_net_pack_HEX.clear();

                //char* 转 QByteArray
                p_echo_net_pack_array = QByteArray(p_echo_net_pack,lenoRecvHEX);

                p_echo_net_pack_HEX = p_echo_net_pack_array.toHex().toUpper();

                qDebug()<<p_echo_net_pack_HEX[128]<<p_echo_net_pack_HEX[129]<<p_echo_net_pack_HEX[130]<<p_echo_net_pack_HEX[131]<<endl;

                char X = '3';
                char Y = '0';

                //判断32帧数据的帧头，从而定位起点位置.
                //若某帧第129~144位分别是3030303030303030，则该帧是起点帧
                if((p_echo_net_pack_HEX[128]== X) && (p_echo_net_pack_HEX[129]== Y) && (p_echo_net_pack_HEX[130]== X) && (p_echo_net_pack_HEX[131]== Y) )
                    isStartFrame = 1;

                /*---------------Mode I: 将脉冲波形显示出来------------*/
                if((mainWindow->AcqMode == 1) && isStartFrame){

                    //p_echo_net_pack_HEX >> pack_HEX_32[]
                    for(int k = 2*pack_count; k<(2*pack_count + 2048) ; k++ )
                        pack_HEX_32[k] = p_echo_net_pack_HEX[k-2*pack_count];

                    //计数收到的包次数
                    pack_count = pack_count + 1024;

                    //每收到32个包时，称为一个事件
                    if(pack_count>=1024*32){
                        isStartFrame = 0;
                        pack_count = 0;

                        //pack_HEX_32[] >> pack_HEX_Display[]

                        memcpy(pack_HEX_Display,pack_HEX_32,sizeof(char)*2048*32);

                        memset(pack_HEX_32,'\0',sizeof(pack_HEX_32)); //清空数组
                    }
                }

                /*---------------Mode II: 直接保存收到的数据------------*/
                if(mainWindow->AcqMode == 2){

                    //CHData << p_echo_net_pack_HEX
                    for(int i=0; i<lenoRecvHEX; i++) {

                        unsigned char usCHDATA =(unsigned char)p_echo_net_pack_HEX[i];

                        for(int j = 0; j<SaveNumber; j++){

                            //如果CHdataj没满，存入CHdataj，跳出循环；否则存入CHdataj+1
                            if(!CHdataArray[j]->isFull()){

                                CHdataArray[j]->push(usCHDATA);

                                break;
                            }
                            else
                                continue;
                        }

                    }//end for
                }
            } //end if

        } //end if
    }
}

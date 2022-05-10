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

            isASCII = mainWindow->isASCII;

            isHEX = mainWindow->isHEX;

            net_pack_size = 0;

            /*----------------ASCII接收-------------------*/
            if(isASCII && (!isHEX)){

                //init array
                p_echo_net_pack[0] = '\0';

                net_pack_size = recvfrom(echo_socket_WIN, p_echo_net_pack, lenoRecv, 0, (sockaddr *)&src_addr_WIN, &src_addr_len);

                if (net_pack_size == SOCKET_ERROR) {

                    qDebug()<<"recvfrom failed with error : "<< WSAGetLastError() <<endl;

                }

                qDebug()<<"Reciving net_pack_size = "<< net_pack_size <<endl;

                //init RECORD_BUF
                bufPtr[0] = '\0';

                //RECORD_BUF << p_echo_net_pack
                memcpy(bufPtr,p_echo_net_pack,lenoRecv);

                pack_count = pack_count + net_pack_size;

                //将p_echo_net_pack传给wave_widget
                if(pack_count>1024000){

                    emit SendtoWidget(p_echo_net_pack);

                    pack_count = 0;
                }

                //CHData << RECORD_BUF
                for(int i=0; i<lenoRecv; i++) {

                    unsigned char usCHDATA =(unsigned char)bufPtr[i];

                    for(int j = 0; j<SaveNumber; j++){

                        //如果CHdataj满了，j++；否则存入CHdataj，然后break
                        if(CHdataArray[j]->isFull())
                            continue;
                        else{
                            CHdataArray[j]->push(usCHDATA);
                            break;}

                    }

                }//end for

            }

            /*----------------HEX接收-------------------*/
            if((!isASCII) && isHEX){

                lenoRecvHEX = lenoRecv * 2;

                //define a new char[]
                p_echo_net_pack[0] = '\0';

                net_pack_size = recvfrom(echo_socket_WIN, (char*)p_echo_net_pack, lenoRecvHEX, 0, (sockaddr *)&src_addr_WIN, &src_addr_len);

                qDebug()<<"Reciving net_pack_size = "<< net_pack_size <<endl;

                //clear QByteArray
                p_echo_net_pack_array.clear();
                p_echo_net_pack_HEX.clear();

                //char* 转 QByteArray
                p_echo_net_pack_array = QByteArray(p_echo_net_pack,lenoRecv);

                p_echo_net_pack_HEX = p_echo_net_pack_array.toHex().toUpper();

                qDebug()<<p_echo_net_pack_HEX[128]<<p_echo_net_pack_HEX[129]<<p_echo_net_pack_HEX[130]<<p_echo_net_pack_HEX[131]<<endl;

                char X = '3';
                char Y = '0';

                //判断32帧数据的帧头，从而定位起点位置.
                //若某帧第129~144位分别是3030303030303030，则该帧是起点帧
                if((p_echo_net_pack_HEX[128]== X) && (p_echo_net_pack_HEX[129]== Y) && (p_echo_net_pack_HEX[130]== X) && (p_echo_net_pack_HEX[131]== Y)
/*                        && p_echo_net_pack_HEX[132]=='3' && p_echo_net_pack_HEX[133]=='0' && p_echo_net_pack_HEX[134]=='3' && p_echo_net_pack_HEX[135]=='0'
                        && p_echo_net_pack_HEX[136]=='3' && p_echo_net_pack_HEX[137]=='0' && p_echo_net_pack_HEX[138]=='3' && p_echo_net_pack_HEX[139]=='0'
                        && p_echo_net_pack_HEX[140]=='3' && p_echo_net_pack_HEX[141]=='0' && p_echo_net_pack_HEX[142]=='3' && p_echo_net_pack_HEX[143]=='0'*/ )
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

                        emit_count++;

                        //(用于刷新波形显示的速率)每触发1次上述事件，emit信号给wave_widget
                        if (emit_count>=50){

                            emit SendtoWidget(pack_HEX_32);

                            emit_count=0;

                            qDebug()<<"Signal emitted ! " <<endl;

                            isStartFrame = 0;
                        }

                        pack_count = 0;

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

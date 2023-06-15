void joo()
{
    std::cout << "[+] Executing joo...\n";
    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::cout << "[-] joo! Done.\n";
}

void foo()
{
    // simulate expensive operation
    std::cout << "[+] Executing foo...\n";
    std::thread fooLocal(joo);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    fooLocal.join();
    std::cout << "[-] foo! Done.\n";
}

void bar()
{
    // simulate expensive operation
    std::cout << "[+] Executing bar...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "[-] bar! Done.\n";
}

void run() {
    int iarr[3] = { 1,2,3 };
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();

    for (auto i : iarr)
    {
        std::cout << i;
    }
    std::cout << " between\n";
    helper2.join();

    std::cout << "Done\n";
}
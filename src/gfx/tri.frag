   #version 330 core
    out vec4 FragColor;
    in vec4 position; 
    void main()
    {
    FragColor = vec4(0.0f, abs(position.y), 0.2f, 1.0f);
    }


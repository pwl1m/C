class TemperatureDashboard {
    constructor() {
        this.temperatureChart = null;
        this.initChart();
        this.loadCSV();
    }

    initChart() {
        const ctx = document.getElementById('temperatureChart').getContext('2d');
        
        const gradient = this.getGradient(ctx, {top: 0, bottom: 400});

        this.temperatureChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: [{
                    label: 'Temperature (°C)',
                    data: [],
                    borderColor: gradient,
                    borderWidth: 4,
                    fill: false,
                }]
            },
            options: {
                responsive: true,
                scales: {
                    x: {
                        type: 'time',
                        time: {
                            unit: 'hour',
                            // tooltipFormat: 'Pp'
                        },
                        title: {
                            display: true,
                            // text: 'Hora'
                        }
                    },
                    y: {
                        title: {
                            display: true,
                            // text: 'Temperature (°C)'
                        }
                    }
                }
            }
        });
    }

    getGradient(ctx, chartArea) {
        const chartHeight = chartArea.bottom - chartArea.top;
        const gradient = ctx.createLinearGradient(0, chartArea.bottom, 0, chartArea.top);
        gradient.addColorStop(0, 'rgba(75, 192, 192, 1)');
        gradient.addColorStop(0.5, 'rgba(255, 206, 86, 1)');
        gradient.addColorStop(1, 'rgba(255, 99, 132, 1)');
        return gradient;
    }

    loadCSV() {
        const csvFilePath = 'temperatura_data.csv';
        this.fetchCSV(csvFilePath);
    }

    fetchCSV(csvFilePath) {
        fetch(csvFilePath)
            .then(response => response.text())
            .then(text => {
                this.processCSV(text);
            })
            .catch(error => {
                console.error('Error fetching the CSV file:', error);
            });
    }

    processCSV(text) {
        const lines = text.split('\n');
        const data = lines.map(line => {
            const parts = line.split(',');
            if (parts.length >= 2) {
                const temperature = parseFloat(parts[0].trim());
                const timestamp = parts[1].trim();
                return { temperature, timestamp };
            }
            return null;
        }).filter(item => item !== null);

        if (data.length > 0) {
            this.updateTemperatureList(data);
            this.updateChart(data);
        } else {
            document.getElementById('temperatureDisplay').innerText = 'No valid data';
        }
    }

    updateTemperatureList(data) {
        const temperatureList = document.getElementById('temperatureList');
        temperatureList.innerHTML = '';
        data.forEach(item => {
            const listItem = document.createElement('li');
            listItem.textContent = `Temperature: ${item.temperature} °C, Timestamp: ${item.timestamp}`;
            temperatureList.appendChild(listItem);
        });

        const latestData = data[data.length - 1];
        document.getElementById('temperatureDisplay').innerText = `Latest Temperature: ${latestData.temperature} °C at ${latestData.timestamp}`;
    }

    updateChart(data) {
        const delay = 500; // Delay  entre cada atualização
        let dataIndex = 0;
        const updateInterval = setInterval(() => {
            const newData = data.slice(0, dataIndex + 1);
            
            this.temperatureChart.data.labels = newData.map(item => new Date(item.timestamp));
            this.temperatureChart.data.datasets[0].data = newData.map(item => item.temperature);
            this.temperatureChart.update();
            
            if (dataIndex === data.length - 1) {
                clearInterval(updateInterval);
            }
            
            dataIndex++;
        }, delay);
    }
}

document.addEventListener('DOMContentLoaded', () => {
    new TemperatureDashboard();
});
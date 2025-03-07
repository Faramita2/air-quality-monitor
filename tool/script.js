let isTestEnvironment = true;

let pendingRequest = null;
let lastSubmitTime = 0;
const SUBMIT_INTERVAL = 15000;

const backgroundImages = [
    'images/bg1.png',
    'images/bg2.png',
    'images/bg3.png',
    'images/bg4.png',
    'images/bg5.png'
];

let config = {
    writeApiKey: '',
    readApiKey: '',
    channelId: ''
};

document.addEventListener('DOMContentLoaded', () => {
    const skinSwitchButton = document.getElementById('skinSwitchButton');
    const envSwitchButton = document.getElementById('envSwitchButton');
    const configButton = document.getElementById('configButton');
    const sneezeButton = document.getElementById('sneezeButton');
    const runnyNoseButton = document.getElementById('runnyNoseButton');
    const sneezeInput = document.getElementById('sneezeCount');
    const responseDiv = document.getElementById('response');
    const retryButton = document.getElementById('retryButton');
    const debugModal = new bootstrap.Modal(document.getElementById('debugModal'));
    const configModal = new bootstrap.Modal(document.getElementById('configModal'));
    const writeApiKeyInput = document.getElementById('writeApiKey');
    const readApiKeyInput = document.getElementById('readApiKey');
    const channelIdInput = document.getElementById('channelId');
    const saveConfigButton = document.getElementById('saveConfigButton');

    setRandomBackground();

    function setRandomBackground() {
        const randomIndex = Math.floor(Math.random() * backgroundImages.length);
        const randomImage = backgroundImages[randomIndex];
        document.body.style.backgroundImage = `url('${randomImage}')`;
    }

    skinSwitchButton.addEventListener('click', () => {
        if (document.body.classList.contains('anime-style')) {
            document.body.classList.remove('anime-style');
            skinSwitchButton.textContent = 'Switch to Anime Style';
            document.body.style.backgroundImage = '';
        } else {
            document.body.classList.add('anime-style');
            skinSwitchButton.textContent = 'Switch to Default Style';
            setRandomBackground();
        }
    });

    envSwitchButton.addEventListener('click', () => {
        isTestEnvironment = !isTestEnvironment;
        updateEnvButtonText();
    });

    updateEnvButtonText();

    configButton.addEventListener('click', () => {
        writeApiKeyInput.value = config.writeApiKey;
        readApiKeyInput.value = config.readApiKey;
        channelIdInput.value = config.channelId;
        configModal.show();
    });

    saveConfigButton.addEventListener('click', () => {
        config.writeApiKey = writeApiKeyInput.value.trim();
        config.readApiKey = readApiKeyInput.value.trim();
        config.channelId = channelIdInput.value.trim();

        if (!config.writeApiKey) {
            alert('Write API Key is required!');
            return;
        }

        configModal.hide();
        updateSubmitButtonState();
    });

    function updateSubmitButtonState() {
        if (!config.writeApiKey) {
            sneezeButton.disabled = true;
            runnyNoseButton.disabled = true;
            responseDiv.innerHTML = `
                <div class="alert alert-danger" role="alert">
                    Please configure the Write API Key first!
                </div>
            `;
        } else {
            sneezeButton.disabled = false;
            runnyNoseButton.disabled = false;
            responseDiv.innerHTML = '';
        }
    }

    updateSubmitButtonState();

    sneezeButton.addEventListener('click', () => {
        const sneezeCount = Math.max(parseInt(sneezeInput.value), 1);
        if (isNaN(sneezeCount)) {
            showResponse('Please enter a valid number of sneezes.', 'danger');
            return;
        }
        sendData(sneezeCount, 0, 'Sneezing');
    });

    runnyNoseButton.addEventListener('click', () => {
        sendData(0, 1, 'Runny Nose');
    });

    retryButton.addEventListener('click', () => {
        if (pendingRequest) {
            sendData(pendingRequest.sneezes, pendingRequest.runnyNose, pendingRequest.eventType);
        }
    });

    function sendData(sneezes, runnyNose, eventType) {
        const currentTime = Date.now();
        if (currentTime - lastSubmitTime < SUBMIT_INTERVAL) {
            const remainingTime = Math.ceil((SUBMIT_INTERVAL - (currentTime - lastSubmitTime)) / 1000);
            showResponse(`Please wait ${remainingTime} seconds before submitting again!`, 'danger');
            return;
        }

        let url = `https://api.thingspeak.com/update?api_key=${config.writeApiKey}`;
        if (sneezes > 0) {
            const fieldSneezes = getFieldName(5);
            url += `&${fieldSneezes}=${sneezes}`;
        }
        if (runnyNose > 0) {
            const fieldRunnyNose = getFieldName(6);
            url += `&${fieldRunnyNose}=${runnyNose}`;
        }

        console.log('Submitting to URL:', url);
        showResponse('Submitting data, please wait...', 'info');
        disableUI();

        pendingRequest = { sneezes, runnyNose, eventType };

        fetch(url)
            .then(response => {
                if (!response.ok) throw new Error(`HTTP Error: ${response.status}`);
                return response.text();
            })
            .then(data => {
                console.log('API Response:', data);
                if (data.trim() === '0') throw new Error('Submission failed: Server returned 0.');
                showResponse('Data submitted successfully!', 'success');
                updateDebugInfo(eventType, sneezes || runnyNose, data);
                debugModal.show();
                pendingRequest = null;
                lastSubmitTime = Date.now();
                startCountdown();
                retryButton.classList.add('d-none');
            })
            .catch(error => {
                console.error('Error:', error.message);
                showResponse('Data submission failed!', 'danger');
                updateDebugInfo(eventType, sneezes || runnyNose, error.message, true);
                debugModal.show();
                enableUI();
                retryButton.classList.remove('d-none');
            });
    }

    function getFieldName(fieldType) {
        return isTestEnvironment ? `field${fieldType + 2}` : `field${fieldType}`;
    }

    function updateDebugInfo(eventType, value, responseData, isError = false) {
        const debugContent = `
            <div class="key">Event Type:</div> <div class="value">${eventType}</div>
            <div class="separator"></div>
            <div class="key">Value Submitted:</div> <div class="value">${value}</div>
            <div class="separator"></div>
            <div class="key">Timestamp:</div> <div class="value">${new Date().toLocaleString()}</div>
            <div class="separator"></div>
            <div class="key">Response:</div> <div class="value ${isError ? 'error' : ''}">${responseData}</div>
        `;
        document.getElementById('debugInfo').innerHTML = debugContent;
    }

    function showResponse(message, type) {
        responseDiv.innerHTML = `
            <div class="alert alert-${type}" role="alert">
                ${message}
            </div>
        `;
    }

    function disableUI() {
        sneezeButton.disabled = true;
        runnyNoseButton.disabled = true;
        sneezeInput.disabled = true;
    }

    function enableUI() {
        sneezeButton.disabled = false;
        runnyNoseButton.disabled = false;
        sneezeInput.disabled = false;
    }

    function startCountdown() {
        let remainingTime = Math.ceil(SUBMIT_INTERVAL / 1000);
        const countdownInterval = setInterval(() => {
            showResponse(`Data submitted successfully! Please wait ${remainingTime} seconds before submitting again.`, 'success');
            remainingTime--;

            if (remainingTime < 0) {
                clearInterval(countdownInterval);
                showResponse('You can submit data again!', 'info');
                enableUI();
            }
        }, 1000);
    }

    function updateEnvButtonText() {
        if (isTestEnvironment) {
            envSwitchButton.textContent = 'Test Environment';
            envSwitchButton.classList.remove('prod-env');
            envSwitchButton.classList.add('test-env');
        } else {
            envSwitchButton.textContent = 'Production Environment';
            envSwitchButton.classList.remove('test-env');
            envSwitchButton.classList.add('prod-env');
        }
    }
});